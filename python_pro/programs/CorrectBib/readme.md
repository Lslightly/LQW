# bib文件的预处理
## 问题描述
[Bibtex](http://www.bibtex.org/) 是用来描述和处理文献列表的工具和文件格式。Bibtex文件的格式见<http://www.bibtex.org/Format/>，文件的扩展名为bib.
bib文件一般与latex文档一起使用. 现在需要在word中复用bib文件已管理word文档所使用的文献引用和文献信息，
一种解决途径是使用[Mendeley](https://www.mendeley.com/reference-management/mendeley-desktop)文献管理工具及其word插件.
但是，mendeley对bib文献条目的展示不太一样，并且不能处理内嵌在里面的latex命令：例如
```
@inproceedings{ brackenbury2019tap,
	author = {Will Brackenbuwery and Abhimanyu Deora and Jillian Ritchey and Jason Vallee and Weijia He and Guan Wang and Michael L. Littman and Blase Ur},
	title = {How Users Interpret Bugs in {Trigger-Action} Programming},
	booktitle = {\bibbrev{HCI}{ACM SIGCHI Conference on Human Factors in Computing Systems }},
	year = {2019},
	address = {Glasgow, Scotland, UK},
}
```
- \bibbrev{A}{B}是自定义的latex命令，它用于控制是简要输出会议名称缩写A、还是详细输出会议的完整名称B
- 在XXX = {YYY}的条目中，如果YYY里面包含有花括号括起的部分，bibtex在处理时会原样输出括号里的内容，而不按缺省方式改变该内容的大小写；
  但是这样的信息导入到mendeley之后，花括号仍然被保留，实际希望去掉这样的花括号。

再如：
```
@inproceedings{ birnbach2019peeves,
    author = {Birnbach, Simon and Eberz, Simon and Martinovic, Ivan},
    title = {Peeves: Physical Event Verification in Smart Homes},
    year = {2019},
    isbn = {9781450367479},
    publisher = {Association for Computing Machinery},
    address = {New York, NY, USA},
    url = {https://doi.org/10.1145/3319535.3354254},
    doi = {10.1145/3319535.3354254},
    booktitle = {\bibconf[26th]{CCS}{2019 ACM SIGSAC Conference on Computer and Communications Security}},
    pages = {1455–1467},
    numpages = {13},
    keywords = {smart home, internet of things, event verification},
    location = {London, United Kingdom},
    series = {CCS ’19}
}

```
- \bibconf[C]{A}{B}是自定义的latex命令，它用于控制是简要输出会议名称缩写C#A、还是详细输出会议的完整名称C#B

- **输入**: 一个bib文件, 一个转换描述
- **输出**: 转换后的bib文件
- **转换规则**
  - 按转换描述指定的规则处理bibbrev或bibconf
  - 处理等号右边花括号或双引号内部花括号扩起的子串，去除掉子串的花括号
  