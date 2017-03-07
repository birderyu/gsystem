# GSystem  

> GSystem是一个轻量级的跨平台基础开发包，也是一个数据结构和工具类的集合。  
> 目标：轻量、高效、跨平台  

GSystem包括以下几个库：  

## GCore  
GCore是GSystem的核心包，包括全局宏定义、跨平台类型定义、数据结构、字符串、容器、工具类等，此外，还有一个Json解析器和一个XML解析器。  
## GGeometry  
GGeometry是一个高效的几何模型包，包括一系列二维几何模型和三维几何模型，它们共同派生自接口GGeometry。此外，还包括了基于几何模型的一些算法和空间索引。  
## GDataTable  
GDataTable包含了一种名为数据表的接口定义，和它的若干种实现。数据表是一种高效、可构建索引、可序列化、支持多种数据格式（包括几何对象）的表数据结构。  
## GSerialization  
GSerialization是一个用于序列化的包，包含了流接口GStream和档案接口GArchive以及它们的一系列功能派生类。其中GStream是流的基类，GArchive用于数据的序列化。  
## GConcurrent  
并发数据结构包，是一个实验性质的包，包含了一些无锁数据结构和用于构建高并发功能的类。  