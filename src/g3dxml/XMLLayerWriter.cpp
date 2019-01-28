#include <g3dxml/XMLLayerWriter.h>
#include <geo3dml/StyleRuleEqualTo.h>
#include <geo3dml/FeatureTypeStyle.h>

using namespace g3dxml;

XMLLayerWriter::XMLLayerWriter() {

}

XMLLayerWriter::~XMLLayerWriter() {

}

bool XMLLayerWriter::Write(geo3dml::Layer* layer, std::ostream& output, SchemaVersion v) {
	output << "<Layer gml:id=\"" << layer->GetID() << "\">" << std::endl
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
			geo3dml::TextFieldValue* textValue = new geo3dml::TextFieldValue(fieldDef.Name());
			textValue->Value(actor->GetBindingFeature()->GetID());
			geo3dml::StyleRuleEqualTo* eqRule = new geo3dml::StyleRuleEqualTo(textValue, fieldDef);
			eqRule->SetSymbolizer(actor->MakeSymbozier());
			featureStyle->AddRule(eqRule);
		}
		layer->AddStyle(featureStyle);
		styleNumber = 1;
	}
	if (styleNumber > 0) {
		output << "<Styles>" << std::endl;
		for (int s = 0; s < styleNumber; ++s) {
			geo3dml::Geo3DStyle* style = layer->GetStyleAt(s);
			WriteStyle(style, output);
		}
		output << "</Styles>" << std::endl;
	}
	output << "</Layer>" << std::endl;
	return true;
}

void XMLLayerWriter::WriteStyle(geo3dml::Geo3DStyle* style, std::ostream& output) {
	output << "<Style>" << std::endl
		<< "<Geo3DStyle gml:id=\"" << style->GetID() << "\">" << std::endl
		<< "<gml:name>" << style->GetName() << "</gml:name>" << std::endl;
	geo3dml::FeatureTypeStyle* featureStyle = dynamic_cast<geo3dml::FeatureTypeStyle*>(style);
	if (featureStyle != NULL) {
		WriteFeatureTypeStyle(featureStyle, output);
	}
	output << "</Geo3DStyle>" << std::endl
		<< "</Style>" << std::endl;
}

void XMLLayerWriter::WriteFeatureTypeStyle(geo3dml::FeatureTypeStyle* featureStyle, std::ostream& output) {
	output << "<se:FeatureTypeStyle>" << std::endl;
	int ruleNumber = featureStyle->GetRuleCount();
	for (int i = 0; i < ruleNumber; ++i) {
		geo3dml::StyleRule* rule = featureStyle->GetRuleAt(i);
		WriteStyleRule(rule, output);
	}
	output << "</se:FeatureTypeStyle>" << std::endl;
}

void XMLLayerWriter::WriteStyleRule(geo3dml::StyleRule* rule, std::ostream& output) {
	output << "<se:Rule>" << std::endl;
	geo3dml::StyleRuleEqualTo* eqRule = dynamic_cast<geo3dml::StyleRuleEqualTo*>(rule);
	if (eqRule != NULL) {
		output << "<ogc:Filter>" << std::endl
			<< "<ogc:PropertyIsEqualTo>" << std::endl;
		output << "<ogc:PropertyName>" << eqRule->GetField().Name() << "</ogc:PropertyName>" << std::endl;
		output << "<ogc:Literal>";
		const geo3dml::FieldValue* fv = eqRule->GetBaseValue();
		switch (fv->ValueType()) {
		case geo3dml::Field::Text: {
			const geo3dml::TextFieldValue* textValue = dynamic_cast<const geo3dml::TextFieldValue*>(fv);
			if (textValue != NULL) {
				output << textValue->Value();
			}
			break;
		}
		case geo3dml::Field::Double: {
			const geo3dml::DoubleFieldValue* doubleValue = dynamic_cast<const geo3dml::DoubleFieldValue*>(fv);
			if (doubleValue != NULL) {
				output << doubleValue->Value();
			}
			break;
		}
		case geo3dml::Field::Integer: {
			const geo3dml::IntegerFieldValue* intValue = dynamic_cast<const geo3dml::IntegerFieldValue*>(fv);
			if (intValue != NULL) {
				output << intValue->Value();
			}
			break;
		}
		case geo3dml::Field::Boolean: {
			const geo3dml::BooleanFieldValue* boolValue = dynamic_cast<const geo3dml::BooleanFieldValue*>(fv);
			if (boolValue != NULL) {
				output << boolValue->Value();
			}
		}
		default:
			break;
		}
		output << "</ogc:Literal>" << std::endl;
		output << "</ogc:PropertyIsEqualTo>" << std::endl
			<< "</ogc:Filter>" << std::endl;
	}
	geo3dml::Symbolizer* sym = rule->GetSymbolizer();
	if (sym != NULL) {
		WriteSymbolizer(sym, output);
	}
	output << "</se:Rule>" << std::endl;
}

void XMLLayerWriter::WriteSymbolizer(geo3dml::Symbolizer* sym, std::ostream& output) {
	geo3dml::SurfaceSymbolizer* surfaceSym = dynamic_cast<geo3dml::SurfaceSymbolizer*>(sym);
	if (surfaceSym != NULL) {
		WriteSurfaceSymbolizer(surfaceSym, output);
	} else {
		geo3dml::LineSymbolizer* lineSym = dynamic_cast<geo3dml::LineSymbolizer*>(sym);
		if (lineSym != NULL) {
			WriteLineSymbolizer(lineSym, output);
		} else {
			geo3dml::PointSymbolizer* pointSym = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
			if (pointSym != NULL) {
				WritePointSymbolizer(pointSym, output);
			}
		}
	}
}

void XMLLayerWriter::WritePointSymbolizer(geo3dml::PointSymbolizer* pointSym, std::ostream& output) {
	output << "<GeoPointSymbolizer>" << std::endl;
	output << "<se:Graphic>" << std::endl
		<< "<se:Size>" << pointSym->GetSize() << "</se:Size>" << std::endl
		<< "</se:Graphic>" << std::endl;
	WriteMaterial(pointSym->GetMaterial(), output);
	output << "</GeoPointSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteLineSymbolizer(geo3dml::LineSymbolizer* lineSym, std::ostream& output) {
	output << "<GeoLineSymbolizer>" << std::endl;
	output << "<se:Stroke>" << std::endl
		<< "<se:SvgParameter name=\"stroke-width\">" << lineSym->GetWidth() << "</se:SvgParameter>" << std::endl
		<< "</se:Stroke>" << std::endl;
	WriteMaterial(lineSym->GetMaterial(), output);
	output << "</GeoLineSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteSurfaceSymbolizer(geo3dml::SurfaceSymbolizer* surfaceSym, std::ostream& output) {
	output << "<GeoSurfaceSymbolizer>" << std::endl;
	geo3dml::Material frontMaterial = surfaceSym->GetFrontMaterial();
	output << "<Front>" << std::endl;
	WriteMaterial(surfaceSym->GetFrontMaterial(), output);
	output << "</Front>" << std::endl;
	if (surfaceSym->IsBackRenderEnabled()) {
		output << "<Back>" << std::endl;
		WriteMaterial(surfaceSym->GetBackMaterial(), output);
		output << "</Back>" << std::endl;
	}
	if (surfaceSym->IsVertexRenderEnabled()) {
		output << "<VertexSymbolizer>" << std::endl;
		geo3dml::PointSymbolizer* pointSym = surfaceSym->GetVertexSymbolizer();
		WritePointSymbolizer(pointSym, output);
		output << "</VertexSymbolizer>" << std::endl;
	}
	if (surfaceSym->IsFrameRenderEnabled()) {
		output << "<FrameSymbolizer>" << std::endl;
		geo3dml::LineSymbolizer* lineSym = surfaceSym->GetFrameSymbolizer();
		WriteLineSymbolizer(lineSym, output);
		output << "</FrameSymbolizer>" << std::endl;
	}
	output << "</GeoSurfaceSymbolizer>" << std::endl;
}

void XMLLayerWriter::WriteMaterial(const geo3dml::Material& m, std::ostream& output) {
	geo3dml::Color diffuseColor = m.GetDiffuseColor();
	geo3dml::Color emissiveColor = m.GetEmissiveColor();
	geo3dml::Color specularColor = m.GetSpecularColor();
	output << "<Material>" << std::endl
		<< "<AmbientIntensity>" << m.GetAmbientIntensity() << "</AmbientIntensity>" << std::endl
		<< "<DiffuseColor>" << diffuseColor.R() << " " << diffuseColor.G() << " " << diffuseColor.B() << "</DiffuseColor>" << std::endl
		<< "<EmissiveColor>" << emissiveColor.R() << " " << emissiveColor.G() << " " << emissiveColor.B() << "</EmissiveColor>" << std::endl
		<< "<Shininess>" << m.GetShininess() << "</Shininess>" << std::endl
		<< "<SpecularColor>" << specularColor.R() << " " << specularColor.G() << " " << specularColor.B() << "</SpecularColor>" << std::endl
		<< "<Transparency>" << m.GetTransparency() << "</Transparency>" << std::endl
		<< "</Material>" << std::endl;
}
