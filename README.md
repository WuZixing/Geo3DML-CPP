# Geo3DML-CPP

Geo3DML C++ SDK.

包含三个库：

1. **geo3dml**

定义Geo3DML规定的数据结构。
其中，几何数据结构是抽象的，开发者可以基于自有系统的内部数据结构来实现，以期达到导入导出Geo3DML数据时避免内存数据相互转换的目的。

编译&链接：

> ```
> include_directories(${GEO3DML_INCLUDE_DIRS})
> ...
> target_link_libraries(${xxx} ${GEO3DML_LIBRARIES})
> ```

2. **g3dxml**

Geo3DML XML文件读写库。仅支持UTF8编码。

编译&链接：

> ```
> include_directories(${G3DXML_INCLUDE_DIRS})
> ...
> target_link_libraries(${xxx} ${G3DXML_LIBRARIES})
> ```


3. **g3dvtk**

可选。基于VTK实现了Geo3DML的几何数据结构。

编译&链接：

> ```
> set(USE_G3DVTK_LIBRARIES ON)
> ...
> include_directories(${G3DVTK_INCLUDE_DIRS})
> ...
> target_link_libraries(${xxx} ${G3DVTK_LIBRARIES})
> ```

4. **示例**

基于*g3dvtk*读取文件。

>```C++
> #include <g3dvtk/ObjectFactory.h>
> #include <g3dxml/XMLReader.h>
> 
> //......
> std::string xmlFilePath = "d:\\data.xml";
> // 构造自定义的Geo3DML对象工厂。
> g3dvtk::ObjectFactory g3dFactory;
> // 读取文件。如不使用自定义的Geo3DML对象工厂（如 g3dvtk::ObjectFactory），即构造 g3dxml::XMLReader 时使用 nullptr 指针，那么 g3dxml::XMLReader 将使用缺省的对象工厂。
> g3dxml::XMLReader xmlReader(&g3dFactory);
> geo3dml::Object* g3dObject = xmlReader.LoadXMLFile(xmlFilePath);  // 该方法可读取工程或者模型。
> // 检查返回的对象类型。
> geo3dml::Model* model = dynamic_cast<geo3dml::Model*>(g3dObject);
> if (model != NULL) {
>   // 按模型处理。
>   // ......
> } else {
>   geo3dml::Project* project = dynamic_cast<geo3dml::Project*>(g3dObject);
>   if (project != NULL) {
>     project->BindFeatureClassesToLayers(&g3dFactory); // 将要素类与图层绑定起来。
>     // 按工程中的*geo3dml::Map*和*geo3dml::Model*来处理。
>     // ......
>   }
> }
>```

详细示例可参考项目[OpenGeo3D@Github](https://github.com/WuZixing/OpenGeo3D)或者[OpenGeo3D@Gitee](https://gitee.com/zhizhi-link/OpenGeo3D)。
