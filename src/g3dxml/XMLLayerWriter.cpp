#include <g3dxml/XMLLayerWriter.h>
#include <geo3dml/StyleRuleEqualTo.h>
#include <geo3dml/FeatureTypeStyle.h>

using namespace g3dxml;

XMLLayerWriter::XMLLayerWriter() {

}

XMLLayerWriter::~XMLLayerWriter() {

}

bool XMLLayerWriter::Write(geo3dml::Layer* layer, std::ostream& output, SchemaVersion v) {
	output << "<Layer>" << std::endl
		<< "<Geo3DLayer gml:id=\"" << layer->GetID() << "\">" << std::endl
		<< "<gml:name>" << layer->GetName() << "</gml:name>" << std::endl;
	geo3dml::FeatureClass* bindingFC = layer->GetBindingFeatureClass();
	if (bindingFC != NULL) {
		output << "<FeatureClass xlink:type=\"simple\" xlink:href=\"#" << bindingFC->GetID() << "\" />" << std::endl;
	}
	int actorNumber = layer->GetActorCount();
	int styleNumber = layer->GetStyleCount();
	if (styleNumber < 1 && actorNumber > 0) {
		geo3dml::Field fieldDef = geo3dml::StyleRule::GetFieldOfFeatureID();
		geo3dml::FeatureTypeStyle* featureStyle = new geo3dml::FeatureTypeStyle();
		featureStyle->SetID(geo3dml::Object::NewID());
		featureStyle->SetName(layer->GetName());
		for (int m = 0; m < actorNumber; ++m) {
			geo3dml::Actor* actor = layer->GetActorAt(m);
			geo3dml::StyleRuleEqualTo* eqRule = new geo3dml::StyleRuleEqualTo(fieldDef.Name(), actor->GetBindingFeature()->GetID());
			eqRule->SetSymbolizer(actor->MakeSymbozier());
			featureStyle->AddRule(eqRule);
		}
		layer->AddStyle(featureStyle);
		styleNumber = 1;
	}
	if (styleNumber > 0) {
		output << "<Styles>" << std::endl;
		for (int s = 0; s < styleNumber; ++s) {
			geo3dml::Style* style = layer->GetStyleAt(s);
			WriteStyle(style, output, v);
		}
		output << "</Styles>" << std::endl;
	}
	output << "</Geo3DLayer>" << std::endl
		<< "</Layer>" << std::endl;
	return true;
}

void XMLLayerWriter::WriteStyle(geo3dml::Style* style, std::ostream& output, SchemaVersion v) {
	output << "<Style>" << std::endl
		<< "<Geo3DStyle gml:id=\"" << style->GetID() << "\">" << std::endl
		<< "<gml:name>" << style->GetName() << "</gml:name>" << std::endl;
	geo3dml::FeatureTypeStyle* featureStyle = dynamic_cast<geo3dml::FeatureTypeStyle*>(style);
	if (featureStyle != NULL) {
		WriteFeatureTypeStyle(featureStyle, output, v);
	}
	output << "</Geo3DStyle>" << std::endl
		<< "</Style>" << std::endl;
}

void XMLLayerWriter::WriteFeatureTypeStyle(geo3dml::FeatureTypeStyle* featureStyle, std::ostream& output, SchemaVersion v) {
	output << "<FeatureStyle>" << std::endl
		<< "<se:FeatureTypeStyle>" << std::endl;
	int ruleNumber = featureStyle->GetRuleCount();
	for (int i = 0; i < ruleNumber; ++i) {
		geo3dml::StyleRule* rule = featureStyle->GetRuleAt(i);
		WriteStyleRule(rule, output, v);
	}
	output << "</se:FeatureTypeStyle>" << std::endl
		<< "</FeatureStyle>" << std::endl;
}

void XMLLayerWriter::WriteStyleRule(geo3dml::StyleRule* rule, std::ostream& output, SchemaVersion v) {
	output << "<se:Rule>" << std::endl;
	geo3dml::StyleRuleEqualTo* eqRule = dynamic_cast<geo3dml::StyleRuleEqualTo*>(rule);
	if (eqRule != NULL) {
		output << "<ogc:Filter>" << std::endl
			<< "<ogc:PropertyIsEqualTo>" << std::endl
			<< "<ogc:PropertyName>" << eqRule->GetFieldName() << "</ogc:PropertyName>" << std::endl
			<< "<ogc:Literal>" << eqRule->GetValueLiteral() << "</ogc:Literal>" << std::endl
			<< "</ogc:PropertyIsEqualTo>" << std::endl
			<< "</ogc:Filter>" << std::endl;
	}
	geo3dml::Symbolizer* sym = rule->GetSymbolizer();
	if (sym != NULL) {
		WriteSymbolizer(sym, output, v);
	}
	output << "</se:Rule>" << std::endl;
}

void XMLLayerWriter::WriteSymbolizer(geo3dml::Symbolizer* sym, std::ostream& output, SchemaVersion v) {
	geo3dml::SurfaceSymbolizer* surfaceSym = dynamic_cast<geo3dml::SurfaceSymbolizer*>(sym);
	if (surfaceSym != NULL) {
		WriteSurfaceSymbolizer(surfaceSym, output, v);
	} else {
		geo3dml::LineSymbolizer* lineSym = dynamic_cast<geo3dml::LineSymbolizer*>(sym);
		if (lineSym != NULL) {
			WriteLineSymbolizer(lineSym, output, v);
		} else {
			geo3dml::PointSymbolizer* pointSym = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
			if (pointSym != NULL) {
				WritePointSymbolizer(pointSym, output, v);
			} else {
				geo3dml::GeoDiscreteCoverageSymbolizer* coverageSym = dynamic_cast<geo3dml::GeoDiscreteCoverageSymbolizer*>(sym);
				if (coverageSym != NULL) {
					WriteGeoDiscreteCoverageSymbolizer(coverageSym, output, v);
				}
			}
		}
	}
}

void XMLLayerWriter::WritePointSymbolizer(geo3dml::PointSymbolizer* pointSym, std::ostream& output, SchemaVersion v) {
	output << "<GeoPointSymbolizer>" << std::endl;
	output << "<se:Graphic>" << std::endl
		<< "<se:Size>" << pointSym->GetSize() << "</se:Size>" << std::endl
		<< "</se:Graphic>" << std::endl;
	WriteMaterial(pointSym->GetMaterial(), output, v);
	output << "</GeoPointSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteLineSymbolizer(geo3dml::LineSymbolizer* lineSym, std::ostream& output, SchemaVersion v) {
	output << "<GeoLineSymbolizer>" << std::endl;
	output << "<se:Stroke>" << std::endl
		<< "<se:SvgParameter name=\"stroke-width\">" << lineSym->GetWidth() << "</se:SvgParameter>" << std::endl
		<< "</se:Stroke>" << std::endl;
	WriteMaterial(lineSym->GetMaterial(), output, v);
	output << "</GeoLineSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteSurfaceSymbolizer(geo3dml::SurfaceSymbolizer* surfaceSym, std::ostream& output, SchemaVersion v) {
	output << "<GeoSurfaceSymbolizer>" << std::endl;
	const geo3dml::PBRMaterial& frontMaterial = surfaceSym->GetFrontMaterial();
	output << "<Front>" << std::endl;
	WriteMaterial(surfaceSym->GetFrontMaterial(), output, v);
	output << "</Front>" << std::endl;
	if (surfaceSym->IsBackRenderEnabled()) {
		output << "<Back>" << std::endl;
		WriteMaterial(surfaceSym->GetBackMaterial(), output, v);
		output << "</Back>" << std::endl;
	}
	if (surfaceSym->IsVertexRenderEnabled()) {
		output << "<VertexSymbolizer>" << std::endl;
		geo3dml::PointSymbolizer* pointSym = surfaceSym->GetVertexSymbolizer();
		WritePointSymbolizer(pointSym, output, v);
		output << "</VertexSymbolizer>" << std::endl;
	}
	if (surfaceSym->IsFrameRenderEnabled()) {
		output << "<FrameSymbolizer>" << std::endl;
		geo3dml::LineSymbolizer* lineSym = surfaceSym->GetFrameSymbolizer();
		WriteLineSymbolizer(lineSym, output, v);
		output << "</FrameSymbolizer>" << std::endl;
	}
	output << "</GeoSurfaceSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteGeoDiscreteCoverageSymbolizer(geo3dml::GeoDiscreteCoverageSymbolizer* coverageSym, std::ostream& output, SchemaVersion v) {
	output << "<GeoDiscreteCoverageSymbolizer>" << std::endl
		<< "</GeoDiscreteCoverageSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteMaterial(const geo3dml::PBRMaterial& m, std::ostream& output, SchemaVersion v) {
	if (v == Schema_1_0) {
		const geo3dml::Color& diffuseColor = m.GetBaseColor();
		const geo3dml::Color& emissiveColor = m.GetEmissiveColor();
		const geo3dml::Color& specularColor = m.GetSpecularColor();
		output << "<Material>" << std::endl
			<< "<DiffuseColor>" << diffuseColor.R() << " " << diffuseColor.G() << " " << diffuseColor.B() << "</DiffuseColor>" << std::endl
			<< "<EmissiveColor>" << emissiveColor.R() << " " << emissiveColor.G() << " " << emissiveColor.B() << "</EmissiveColor>" << std::endl
			<< "<SpecularColor>" << specularColor.R() << " " << specularColor.G() << " " << specularColor.B() << "</SpecularColor>" << std::endl
			<< "<Transparency>" << 1 - diffuseColor.A() << "</Transparency>" << std::endl;
		const geo3dml::Texture& texture = m.GetBaseTexture();
		if (texture.IsValid()) {
			output << "<Texture>" << std::endl
				<< "<ParameterizedTextureType>" << std::endl
				<< "<ImageURI>" << texture.GetImageURI() << "</ImageURI>" << std::endl
				<< "<MimeType>" << texture.GetImageMime() << "</MimeType>" << std::endl
				<< "<WrapMode>";
			switch (texture.GetWrapMode()) {
			case geo3dml::Texture::WrapMode::Repeat:
				output << "Wrap";
				break;
			case geo3dml::Texture::WrapMode::MirrorRepeat:
				output << "Mirror";
				break;
			case geo3dml::Texture::WrapMode::ClampToEdge:
				output << "Clamp";
				break;
			case geo3dml::Texture::WrapMode::ClampToBorder:
				output << "Border";
				break;
			default:
				output << "None";
				break;
			}
			output << "</WrapMode>" << std::endl;
			if (texture.GetWrapMode() == geo3dml::Texture::WrapMode::ClampToBorder) {
				const geo3dml::Color& color = texture.GetBorderColor();
				output << "<BorderColor>" << color.R() << ' ' << color.G() << ' ' << color.B() << ' ' << color.A() << "</BorderColor>" << std::endl;
			}
			output << "</ParameterizedTextureType>" << std::endl
				<< "</Texture>" << std::endl;
		}
		output << "</Material>" << std::endl;
	} else {
		output << "<PBRMaterial>" << std::endl;
		const geo3dml::Color& baseColor = m.GetBaseColor();
		const geo3dml::Texture& baseTexture = m.GetBaseTexture();
		if (baseTexture.IsValid()) {
			WriteTexture("BaseTexture", baseTexture, output, v);
		} else {
			output << "<BaseColor>" << baseColor.R() << " " << baseColor.G() << " " << baseColor.B() << baseColor.A() << "</BaseColor>" << std::endl;
		}
		const geo3dml::Texture& normalTexture = m.GetNormalTexture();
		if (!normalTexture.IsValid()) {
			WriteTexture("NormalTexture", normalTexture, output, v);
		}
		const geo3dml::Texture& oclussionTexture = m.GetOcclusionTexture();
		if (!oclussionTexture.IsValid()) {
			WriteTexture("OcclusionTexture", oclussionTexture, output, v);
		}
		const geo3dml::Color& emissiveColor = m.GetEmissiveColor();
		output << "<EmissiveColor>" << emissiveColor.R() << " " << emissiveColor.G() << " " << emissiveColor.B() << "</EmissiveColor>" << std::endl;
		output << "<Metallic>" << m.GetMetallic() << "</Metallic>" << std::endl
			<< "<Roughness>" << m.GetRoughness() << "</Roughness>" << std::endl;
		const geo3dml::Color& specularColor = m.GetSpecularColor();
		output << "<SpecularColor>" << specularColor.R() << " " << specularColor.G() << " " << specularColor.B() << "</SpecularColor>" << std::endl;
		output << "<IndexOfRefraction>" << m.GetIndexOfRefraction() << "</IndexOfRefraction>" << std::endl;
		output << "</PBRMaterial>" << std::endl;
	}
}

void XMLLayerWriter::WriteTexture(const std::string& texTag, const geo3dml::Texture& tex, std::ostream& output, SchemaVersion v) {
	output << "<" << texTag << ">" << std::endl
		<< "<ParameterizedTexture>" << std::endl;
	if (!tex.IsImageEmpty()) {
		output << "<Image>" << std::endl
			<< "<URI>" << tex.GetImageURI() << "</URI>" << std::endl
			<< "<MimeType>" << tex.GetImageMime() << "</MimeType>" << std::endl
			<< "</Image>" << std::endl;
	}
	if (!tex.IsGBSymbolEmpty()) {
		const geo3dml::GBSymbol& gbSymbol = tex.GetGBSymbol();
		const geo3dml::Color& strokeColor = gbSymbol.GetStrokeColor();
		const geo3dml::Color& fillColor = gbSymbol.GetFillColor();
		output << "<GBSymbol>" << std::endl
			<< "<Code>" << gbSymbol.GetCode() << "</Code>" << std::endl
			<< "<Stroke>" << strokeColor.R() << ' ' << strokeColor.G() << ' ' << strokeColor.B() << "</Stroke>" << std::endl
			<< "<Fill>" << strokeColor.R() << ' ' << strokeColor.G() << ' ' << strokeColor.B() << "</Fill>" << std::endl
			<< "</GBSymbol>" << std::endl;
	}
	output << "<WrapMode>";
	switch (tex.GetWrapMode()) {
	case geo3dml::Texture::WrapMode::Repeat:
		output << "Wrap";
		break;
	case geo3dml::Texture::WrapMode::MirrorRepeat:
		output << "Mirror";
		break;
	case geo3dml::Texture::WrapMode::ClampToEdge:
		output << "Clamp";
		break;
	case geo3dml::Texture::WrapMode::ClampToBorder:
		output << "Border";
		break;
	default:
		output << "None";
		break;
	}
	output << "</WrapMode>" << std::endl;
	if (tex.GetWrapMode() == geo3dml::Texture::WrapMode::ClampToBorder) {
		const geo3dml::Color& color = tex.GetBorderColor();
		output << "<BorderColor>" << color.R() << ' ' << color.G() << ' ' << color.B() << ' ' << color.A() << "</BorderColor>" << std::endl;
	}
	output << "</ParameterizedTexture>" << std::endl
		<< "</" << texTag << ">" << std::endl;
}
