# XML文档

是由 XML 编程语言编写的文档，XML 编程语言是：可扩展标记编程语言。这种语言的书写不是以行为单位，而是以标签为单位。、

在 XML 中，没有预先定义好的标签，想写什么标签就写什么标签。

XML 诞生于 1996，最初作为【网页】来使用，现在在 Java 中使用 XML 代替 properties 作为配置文件。

# 第一个 XML 程序

在 IDEA 中，右键新建一个文件时，在菜单中是没有 XML 文件的选项的，需要先激活：Settings --> Editor --> File and Code Templates

![image-20240205223256586](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402052233862.png)

```xml
<?xml version="1.0" encoding="UTF-8" ?>
```

## XML 语法

HTML 是从 XML 演化来的，所以 HTML 的语法绝大多数来自于 XML。

**一个 XML 文档必须以一个【根目录标签】为开始，其他标签必须作为【根目录标签】的直接子标签或间接子标签出现。**标签名都是随意写的。比如：

```xml
<学校 name="JCUT">
    <班级 name="CS1">
        <学生 name="mike"></学生>
    </班级>
</学校>
```

这些标签名和标签的属性名都是自己定义的，没有关键字。

因为这种 XML 文档是以树形结构来存在的，所以用来描述配置信息的时候就非常方便管理，所以Java使用 XML 文档来作为配置文件。

**XML 中区分英文的大小写**，HTML 中不区分英文的大小写。

**XML 标签中的属性内容必须使用一对双引号或单引号包起来**，HTML 中可用可不用。 

# XML 文档的读取方式

在实际开发中，一般使用 DOM 读取方式来读取 XML 文档。

## SAX读取方式

根据开发人员的需要，一次将若干个满足条件的标签加载到内存中。一般用于读取标签较少的 xml 文档。

比如有个 xml 文档，可以根据需要，只将所有的 div 标签给加载到内存中，其他的标签不会被加载到内存中。：

```xml
<abc>
	<div>10</div>
    <div>20</div>
</abc>
```

**优点**：节省内存

**缺点**：如果读取大量的标签时，运行效率相对较低。

## DOM读取方式

一次性将 XML 文档中的所有内容加载到内存中。

**缺点**：浪费内存

**优点**：如果读取大量标签的时候，此时由于是在内存中进行定位，所以运行速度较快。

# XML 约束文档

作用：

+ 设置可以在当前 XML 文档中声明的【标签类型名】
+ 设置可以在标签中出现的【属性名】
+ 设置标签之间的父子关系和兄弟关系

分类：

+ DTD 约数文档：简单约数文档，dtd 文档本身也是一个特殊的 XML 文档
+ SCHEMA 约束文档：高级约束文档

## 如何给xml文档绑定约束

在同一个 XML 文档中，只能出现一种约束文档。

## DTD

使用以下格式代码：
```xml
<!DOCTYPE web-app SYSTEM "web-app.dtd">
```

现在有一个 web-app.dtd 约束文档：

```xml
<?xml version="1.0" encoding="UTF-8" ?>

<!ELEMENT web-app (servlet*，servlet-mapping* ，welcome-file-list?) >
<!ELEMENT servlet (servlet-name, description?, (servlet-class|jsp-file))>
<!ELEMENT servlet-mapping (servlet-name ,url-pattern)>
<!ELEMENT servlet-name (#PCDATA)>
<!ELEMENT servlet-class (#PCDATA)>
<!ELEMENT url-pattern (#PCDATA)>
<!ELEMENT welcome-file-list (welcome-file+)>
<!ELEMENT welcome-file (#PCDATA)>
<!ATTLIST web-app version CDATA #IMPLIED>
```

+ `<!ELEMENT 标签名>`：声明可以出现在 XML 文档中的标签名
+ `<!ATTLIST 标签名 属性名>`：声明可以出现在当前标签内部的属性名称
+ `<!ELEMENT 标签名 (子标签名)>`：设置子标签必须出现在父标签内部，且只能出现一次。
+ `<!ELEMENT 标签名 (子标签名?)>`：设置子标签可以出现在父标签的内部，也可以不出现。并且，这个子标签如果出现，也只能出现一次。
+ `<!ELEMENT 标签名 (子标签名*)>`：设置子标签可以出现在父标签的内部，也可以不出现。并且，这个子标签如果出现，可以出现多次。
+ `<!ELEMENT 标签名 (子标签名+)>`：设置子标签必须出现在父标签内部，且可以出现多次。
+ `<!ELEMENT 标签名 (#PCDATA)>`：设置当前标签没有子标签
+ `<!ELEMENT 标签名 ((子标签名1|子标签名2))>`：设置两个子标签必须有一个出现在父标签内部，且不能同时出现。
+ `<!ELEMENT 标签名 (子标签名1,子标签名2)>`：设置两个子标签必须有都出现在父标签内部，且子标签1在前，子标签2在后。

## SCHEMA


```xml
<xsd:schema xm1ns="http://www.W3.org/2001/XMLSchema"
        targetNamespace="http://www. example .org/web-app_ 2_ .5"
        xmlns:xsd="http://www.W3.org/2001/XMLSchema"
        xmlns:tns="http://www.example.org/web-app_ 2_5"
        elementFormDefault=”qualified">
                                      
    <xsd:element name= "web-app" >
        <xsd:complexType>
			<xsd:choice minOccurs="0" maxOccurs="unbounded">
				<xsd:element name="servlet">
					<xsd:complexType>
						<xsd:sequence>
                            <xsd:element name="servlet-name"></xsd:element>
                            <xsd:element name="servlet-class"></xsd:element>
						</xsd:sequence>
					</xsd:complexType>
				</xsd:element>
                <xsd:element name=”servlet-mapping" >
                    <xsd:complexType>
                            <xsd:sequence>
                            <xsd:element name="servlet-name" ></xsd:element>
                            <xsd:element name="url-pattern"></xsd:element>
                        </xsd:sequence>
                    </xsd:complexType>
                </xsd:element>
                <xsd:element name= "welcome-file-list">
                    <xsd:complexType>
                        <xsd:sequence>
                        	<xsd:element name= "welcome-file" maxoccurs="unbounded"></xsd:element>
                        </xsd:sequence>
                    </xsd:complexType>
                </xsd:element>
			</xsd:choice>
            <xsd :attribute name="version" type="double" use="optional"></xsd:attribute>
        </xsd:complexType>
    </xsd:element>
</xsd:schema>
```

# 解析XML

解析 XML 文件的方法：DOM、DOM4J、SAX

## 1 DOM4J 

### 1.1 导入jar包

```xml
<!-- https://mvnrepository.com/artifact/org.dom4j/dom4j -->
<dependency>
    <groupId>org.dom4j</groupId>
    <artifactId>dom4j</artifactId>
    <version>2.1.4</version>
</dependency>
```

### 1.2 DOM4J的常用对象

+ SAXReader：读取 XML 文件到 Document 树结构文件对象
+ Document：是一个 xml 文档对象树，类比 Html 文档对象
+ Element：元素节点。通过 Document 对象可以查找单个元素。

### 1.3 解析步骤

第一步：创建解析器

```java
SAXReader reader = new SAXReader();
```

第二步：通过解析器 read 方法获取 Document 对象：

```java
Document doc = reader.read("XML.xml");
```

第三步：获取 xml 根节点

```java
Element root = doc.getRootElement();
```

第四步：遍历解析子节点

### 1.4 实例

先准备一个 students.xml 文件：

```xml
<?xml version="1.0" encoding="UTF-8" ?>

<students>
    <student>
        <name>做什么</name>
        <college>Java学院</college>
        <telephone>123456789</telephone>
        <notes>男，啊积分卡收到了尽快发货</notes>
    </student>
    <student>
        <name>力学</name>
        <college>Java学院</college>
        <telephone>789456</telephone>
        <notes>男，啊积分卡收到了尽快发货</notes>
    </student>
</students>
```

然后导入DOM4J的包，导入jUnit的包，使用测试方法来测试。

```java
@Test
public void testDom4j() throws Exception {
    // 创建解析器
    SAXReader reader = new SAXReader();
    // 通过解析器的read方法将配置文件读取到内存中，生成一个Document对象树
    Document document = reader.read("src/main/resources/students.xml");
    // 获取根节点
    Element root = document.getRootElement();
    // 通过 Iterator 遍历根节点 root 获取子节点 student
    for (Iterator<Element> iterator = root.elementIterator(); iterator.hasNext(); ) {
        // 获取 student 子节点对象
        Element stu = (Element) iterator.next();
        // 遍历 student 子节点中的节点元素
        for (Iterator<Element> stuIt = stu.elementIterator(); stuIt.hasNext(); ) {
            Element innerElt = stuIt.next();
            // 获取该节点元素的文本
            String val = innerElt.getStringValue();
            System.out.println(val);
        }
    }

}
```

## 2 SAX

### 2.1 方式

事件驱动，边读边写。
优点：无需将整个文档加载到内存中，内存消耗少，适合解析特别大的xml文件。

### 2.2 步骤

第一步：创建解析工厂，通过 newInstance() 方法获取：

```java
SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
```

第二步：创建解析器

```java
SAXParser saxParser = saxParserFactory.newSAXParser();
```

第三步：执行 parser 方法，传入两个参数：xml文件路径、事件处理器

```java
saxParser.parser("person.xml", new MyDefaultHandler1());
```

### 2.3 实例

先准备一个 person.xml 文件：

```xml
<?xml version="1.0" encoding="UTF-8" ?>

<person>
    <p1>
        <name>做什么</name>
        <age>23</age>
    </p1>
    <p1>
        <name>yyyy</name>
        <age>23</age>
    </p1>
</person>
```

使用 SAX 不需要导入另外的包，在 javax 库中有。

```java
@Test
public void testSAX() throws Exception {
    // 创建解析工厂
    SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
    // 创建解析器
    SAXParser saxParser = saxParserFactory.newSAXParser();
    // 通过解析器的parse方法
    saxParser.parse("src/main/resources/person.xml", new MyDefaultHandler());
}
```

其中有个 MyDefaultHandler 类：

```java
class MyDefaultHandler  extends DefaultHandler {
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
        System.out.print("<" + qName + ">");
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        System.out.print("</" + qName + ">");
    }

    @Override
    public void characters(char[] ch, int start, int length) throws SAXException {
        System.out.print(new String(ch, start, length));
    }
}
```

这个类，需要继承 DefaultHandler 类，并且重写他的三个方法。

## 3 DOM4J和xPath

使用 Dom4j 的 xPath 解析 xml 文件。
xPath 语法地址：[xPath](https://www.w3school.com.cn/xpath/xpath_syntax.asp)

xPath 使用路径表达式来选取 xml 文档中的节点或节点集。节点是通过沿着路径（path）或者步（steps）来选取的。

### 3.1 实例

需要使用 xPath 语法，就需要使用到 jaxen 的 jar 包，先引入这个包：

```xml
<!-- https://mvnrepository.com/artifact/jaxen/jaxen -->
<dependency>
    <groupId>jaxen</groupId>
    <artifactId>jaxen</artifactId>
    <version>1.1.6</version>
</dependency>
```

准备一个 config.xml 文件：

```xml
<?xml version="1.0" encoding="UTF-8" ?>

<config>
    <database-info>
        <driver-name>com.mysql.cj.jdbc.Driver</driver-name>
        <url>jdbc:mysql://localhost:3306/test</url>
        <user>root</user>
        <password>1234</password>
    </database-info>
</config>
```

然后测试：

```java
@Test
public void testXPath() throws Exception {
    // 创建解析器
    SAXReader saxReader = new SAXReader();
    // 通过解析器的方法将配置文件读取到内存中，生成一个document对象树
    Document document = saxReader.read("src/main/resources/config.xml");
    //  driver-name节点元素的路径为：config > database-info > driver-name
    //  driver-name节点元素的xpath路径为：/config/database-info/driver-name
    // 通过 xpath 获取节点元素
    Node node = document.selectSingleNode("/config/database-info/driver-name");
    // 获取节点对象的文本内容
    String driverName = node.getStringValue();
    System.out.println(driverName);

    // url节点元素对象的路径：config > database-info > url
    // url 的xpath对象：/config/database-info/url 或者 config//url 或者 //url
    Node node1 = document.selectSingleNode("config//url");
    String url = node1.getStringValue();
    System.out.println(url);

    // user节点同上
    Node node2 = (Node)document.selectObject("//user");
    String user = node2.getText();
    System.out.println(user);
}
```

假如现在 <driver-name> 标签有一个 name 属性，值为 aaa，即：

```xml
<driver-name name="aaa">com.mysql.cj.jdbc.Driver</driver-name>
```

如果想获取该节点的属性值，可以使用节点对象的 attribute 方法获取这个属性对象：

```java
SAXReader saxReader = new SAXReader();
Document document = saxReader.read("src/main/resources/config.xml");
Element elt = (Element) document.selectSingleNode("//driver-name");
Attribute name = elt.attribute("name");
System.out.println(name.getStringValue());
```

+ 需要注意的是，`document.selectSingleNode("//driver-name")` 返回的对象一定要转成 Element 类型，因为 Element 类型有 attribute 方法，但是 Node 类型的对象没有该方法。

或者可以直接使用节点对象的 attributeValue("") 方法：

```java
System.out.println(elt.attributeValue("name"));
```

## 4 使用xPath对象

准备一个 bookstore.xml 文件：

```xml
<?xml version="1.0" encoding="ISO-8859-1"?>

<bookstore>
    <book>
        <title lang="eng">Harry Potter</title>
        <price>29.99</price>
    </book>
    <book>
        <title lang="eng">Learning XML</title>
        <price>39.95</price>
    </book>
</bookstore>
```

使用 DocumentBuilder 类将 xml 文档解析为一棵树，会获取到一个 Document，这个 Document 类是 org.w3c.dom 中的接口。这个 DocumentBuilder 对象是通过 DocumentBuilderFactory 来获取的。

将 xml 文档转换成树之后，就需要使用 XPath 对象来解析 xml 文档。XPath 对象位于 javax.xml.xpath 包下。XPath 对象只能通过 XPathFactory 对象来实例化。

```java
@Test
public void testXPathObj() throws Exception{
    // 首先将xml文档解析为一颗树的结构
    // 先获取DocumentBuilder对象
    DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();  // 创建解析工厂
    DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();  // 创建解析器
    org.w3c.dom.Document doc = documentBuilder.parse("src/main/resources/bookstore.xml");  // 读取配置文件
    // 创建XPath对象
    XPath xPath = XPathFactory.newInstance().newXPath();

    // 获取bookstore节点下book属性category值为web下的第二个title节点的文本内容
    // bookstore -> book[@category='web'][2] -> title
    // xPath: bookstore/book[@category='web'][2]/title/text()
    String titlePath = "bookstore/book[@category='web'][2]/title/text()";
    String titleValue = (String) xPath.evaluate(titlePath, doc, XPathConstants.STRING);
    System.out.println(titleValue);

    // 获取bookstore节点下book属性category值为web的title的属性lang为en的节点内容
    // bookstore -> book[@category='web'] -> title[@lang='en']
    // xpath: bookstore/book[@category='web']/title[@lang='en']/text()
    titlePath = "bookstore/book[@category='web']/title[@lang='en']/text()";
    titleValue = (String)xPath.evaluate(titlePath, doc, XPathConstants.STRING);
    System.out.println(titleValue);

    // 获取bookstore节点下book属性category值为cooking的title的属性lang的值
    // bookstore -> book[@category='cooking'] -> title -> @lang
    // xpath: bookstore/book[@category='cooking']/title/@lang
    titlePath = "bookstore/book[@category='cooking']/title/@lang";
    titleValue = (String)xPath.evaluate(titlePath, doc, XPathConstants.STRING);
    System.out.println(titleValue);

    // 获取bookstore节点下所有book的节点集合
    // bookstore -> book
    // xpath: bookstore/book
    titlePath = "bookstore/book";
    NodeList list = (NodeList)xPath.evaluate(titlePath, doc, XPathConstants.NODESET);
    // 遍历集合
    for (int i = 0; i < list.getLength(); i++) {
        org.w3c.dom.Node item = list.item(i);  // 获取到每一个节点对象
        // 解析每一个对象的文本内容
        String title = (String) xPath.evaluate("title", item, XPathConstants.STRING);
        String price = (String) xPath.evaluate("price", item, XPathConstants.STRING);
        System.out.println(title + " " + price);
    }
}
```

