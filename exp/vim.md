## vim三种模式
* 命令模式：删除行，复制行，移动光标，粘贴等
* 编辑模式：编辑
* 尾行模式：在尾行输入命令对文件进行操作——搜索，替换，保存，退出，撤销，高亮等
## vim打开文件方式
* vim 文件路径(打开或生成指定文件)
* vim +数字 文件路径(打开指定文件，并将光标移到指定行)
* vim +/(关键词) 文件路径(打开指定文件，并且高亮指定关键词)
* vim 路径1 路径2 ... 路径n(同时打开多个文件)
## 命令模式
### 光标移动
* 行首——^
* 行尾——$
* 首行——gg <=> (
* 尾行——G <=> )
* 翻屏
   - 向上翻屏——PgUp <=> ctrl+b(backward)
   - 向下翻屏——PgDn <=> crtl+f(forward)
### 复制粘贴
* 复制光标所在行——yy，粘贴——p
* 以光标所在行为准，向下复制几行(包含当前行)——数字yy
* 可视化复制——ctrl+v,yy,p
### 剪切(删除)
* 剪切(删除)光标所在行——dd,p粘贴最近一次删除
* 剪切(删除)光标所在行为准，向下剪切(删除)几行(包含当前行)——数字dd
* 剪切(删除)光标所在当前行，但是删除之后下一行不上移——D
### 撤销/恢复
* 撤销——:u(不属于命令模式) <=> u (undo)
* 恢复——ctrl+r
### 光标快速移动
* 移动到指定行——数字G
* 当前光标为准上下左右移动n行——数字↑/↓/←/→
* 末行模式下：移动到指定的行——:数字
## 模式切换
* 输入:(英文模式)，从命令模式到末行模式
* 按1或2下ESC，或删除所有命令，从末行模式到命令模式
## 末行模式
### 保存
* :w (写入并保存)
* :w (路径) (写入...(另存为))
### 退出
* :q(退出)
* :wq(写入保存并退出)
* :q!(不保存退出)
* :!外部终端命令(eg:":!ls")
### 查找
* /关键词
    - 切换上/下一个结果N/n
### 取消高亮
* :nohl (no highlight)
### 替换
* :s/被替换的关键词/新的关键词 (string replace)(替换光标所在行的第一个符合条件的关键词)
* :s/被替换的关键词/新的关键词/g (替换光标所在行的所有符合条件的关键词)
* :%s/被替换的关键词/新的关键词 (替换整个文件中每行第一个符合条件的关键词)
* :%s/被替换的关键词/新的关键词/g (替换整个文件中符合条件的关键词)
* %表示整个文件
* g(global)表示全局
### 显示行号
* :set nu
* 取消显示——:ste nonu
### 打开多个文件后切换文件
* 查看当前已经打开的文件——:files
    - %a ——当前正打开的文件(active)
    - \# ——表示上一个打开的文件
    - \+ ——表示有修改
* 切换文件方式
    - :open 文件名
    - :bn/:bp (切换到next/previous文件)
## 编辑模式
### 进入方式
* 从命令模式进入
* i:表示光标所在字符前插入
* a:表示光标所在字符后插入
### 退出方式
* ESC
### 实用功能
* 代码着色
   - 显示——:syntax on(syntax表示语法)
   - 关闭显示——:syntax off
* vim中计算器的使用
   - 计算公式，可用计算器
   - 进入编辑模式，按下ctrl+r，输入“=”,输入要计算的式子，会将结果输入至“位置
## 扩展
### vim配置
* 三种配置情况：
   - 末行模式输入的配置是临时的
   - 个人配置文件(~/.vimrc,如果没有，可以自行新建)
   - 全局配置文件(vim自带,/etc/vimrc)
* .vimrc(个人配置文件)配置
   - 例如：set nu
   - 如果与全局配置文件冲突以个人为准，若个人没有设置，则以全局为准
### 异常退出
   - 在编辑文件是没有正常的wq，而是突然关闭终端，再次打开会粗线异常退出提示
   - 解决办法：将交换文件(在编程时临时产生的文件)删除
### 别名机制
   - 创建属于自己的自定义命令
   - 依靠别名映射文件：~/.bashrc
   - alias cls='clear'
   - 如果想使用，必须重新登录当前用户
### 退出方式
   - :q或者:wq
   - **:x**(保存退出)
       - 在文件没有修改的情况下表示退出，在文件修改的情况下表示保存退出
       - 如果文件没有被修改，但使用wq退出，则文件的修改时间会更新(混淆用户对文件修改时间的认定)，用x退出，则文件修改时间不会更新
   - **:X**(加密文件)
        - 保存密码生效

#### 2021/1/20

*   ``d4w`` won't include the first character after ``4w``
*   ``d4e`` will delete the last character after ``4e``
*   ``S`` will change the whole line. It's equal to ``cc``

*	x  stands for  dl  (delete character under the cursor)
*	X  stands for  dh  (delete character left of the cursor)
*	D  stands for  d$  (delete to end of the line)
*	C  stands for  c$  (change to end of the line)
*	s  stands for  cl  (change one character, and change vim mode into Insert Mode)
*	S  stands for  cc  (change a whole line)
*   V  visual mode select a whole line
*   CTRL-V  select a visual block

*   in visual mode, ``o`` takes me to another side of the select line. In blockwise selection, ``o`` takes me to one of the other corners, while ``O`` takes me to the other corner in the same line.

#### 2021/1/21

*   ``p`` puts part of a line deleted just now just after the cursor
*   it will also puts a line below the cursor

*   ``P`` instead puts before the cursor or above the cursor

*   ``Y`` yanks the whole line, while ``D`` deletes from the cursor to the end of the line.

*   ``"*yy`` copy a line to the clipboard
*   ``"*p`` put text from the clipboard

*   ``daw`` deletes a word if the cursor is in the word.

*   ``cis`` means changing Inner Sentence

*   some differences between ``cis`` and ``cas``
    *   ``cis`` won't delete the white space after the sentence
    *   ``cas`` however will also delete the white space

*   ``das`` will delete a sentence including the white space after it

*   ``vas`` can include a sentence in visual mode

*   text objects
    *   For non-block objects
        *   "a" will include the white space after the text object
        *   "i" won't
    *   For a block object
        *   "a" will include the braces
        *   "i" won't. "i" means "Inner"


*   ``~`` change case of the character under the cursor
*   ``I`` moves the cursor to the first non-blank in the line and enter the insert mode
*   ``A`` moves the cursor to the end of the line and append

*   ``ge`` moves the cursor to the end of the last word
*   ``W`` & ``E`` will only consider the white space as the boundary

*   ``H`` moves the cursor to the "Home"(Top) place of what you can see.
*   ``M`` moves the cursor to the "Middle" place of what you can see.
*   ``L`` moves the cursor to the "Last" place of what you can see.
*   ``zz`` to see the context of the line with the cursor
*   ``zt`` puts the cursor line to the top of the screen
*   ``zb`` the bottom

*   ``.``(dot) used in searching matches any existing character
>   ``\.`` really means a dot



******

#### 2021/1/23

##### topics about "file"

*   when open a sequence of files, use ``:next`` to edit the next file.
*   use ``:wnext`` to ``write`` and go to the ``next`` file. Add ! to abandon changes.
*   use ``:args`` to know where you are
*   use ``CTRL-^`` to jump from file to file
*   ```"`` records where you leave the file
*   ```.`` records where you made the last change
*   uppercase mark like "mB" will set "B" as a global mark.
*   use ``:marks M`` to see where "M" marks

*   ``"fyas`` means yanking a sentence and putting it to the "f" register
*   ``"fp""`` surely means putting the content in the "f" register
*   ``ge`` means moving the cursor to the last word's end.
*   ``:write >> logfile`` will append the text of current file into the "logfile".

*   ``vim -R file`` edits the file read-only
*   ``:saveas move.c`` save as another file
*   ``:file move.c`` rename the file

##### topics about "splitting windows" in |usr_08.txt|

*   ``CTRL-W CTRL-W`` or ``CTRL-W w`` is used to jump between windows
*   ``:close`` to close the window
*   ``:only`` to close all other windows
*   ``:split two.c`` will open a new window and edit the given file
*   ``:new`` will open a new and empty file
*   ``4 CTRL-W +`` will make the window four lines higher
*   ``CTRL-W _`` to make a window as high as it can be
*   ``:vnew`` is used to open a vertically split new and empty window
*   ``CTRL-W K`` the second uppercase "K" means move the window to the very top
*   to command all windows, use ``all`` after normal command
*   to open a window for all arguments, use ``-o`` in the command line, like ``vim -o 1.txt 2.txt``
*   ``-O`` gets vertically split windows

*   use ``vimdiff`` to see the difference between two files
*   ``zo`` to open a fold and ``zc`` to close a fold

*   ``:tabedit file`` will open a new tab
*   ``gt`` will goto another tab
*   ``:tab split`` will make a new tab in one window

##### topic about "making big changes" in usr_10.txt

*   command sequence will be stores in regsiters and you can put it in the end of the file and change it and again yank it back to the register. You don't have to again recording the whole command sequence, but just **modify a bit**.
*   ``qC`` records to the "c" register and **appends**

*   ``:s/ / /c``
    *   y Yes
    *   n No
    *   a all
    *   q quit, no more
    *   l last, then quit

#### 2021/1/24

*   ``.`` in ranges means **current line**
*   ``$`` in ranges means **the last line of the file**

>   eg: ``:.,$s/yes/no`` means changing the first yes to no from current line to the last line of the file

*   ``?^Chapter?`` finds the line above the current position that matches this pattern.
*   ``/^Chapter/`` to search forward
*   ``:?^Chapter?,/^Chapter/s=grey=gray=g`` means changing grey to gray in **this Chapter**
*   use **offset** for ranges, like ``:.+3,$-6s/...``, which means three lines below the cursor and 6 lines above the last line
*   marks can be used for ranges. use "t" mark by ``'t"
*   '< is the mark placed at the start of the Visual selection, '> the end
*   use "5:" to get a range ":.,.+4"

##### global command

*   ``g+//+s/foobar/barfoo/g`` means finding "//" pattern in the global file and chaning "foobar" to "barfoo"

##### Visual block mode

*   ``I{string}<Esc>`` inserts {string} in each line, just left of **the visual block**
*   ``A`` works the same way, but it will also append characters in the same column place
*   use ``$`` to append in the end of each line.
*   ``c{string}<Esc>`` to change the visual block
*   ``C...`` to change from the left edge of the block to the end of the line
*   ``~`` swap case
*   ``U`` make Uppercase
*   ``u`` make lowercase
*   ``>`` to shift right
*   ``<`` to shift left
*   ``J`` joins all selected lines together into one line

##### reading and writing part of a file

*   ``:read file`` will append the file content below the cursor line. It also accepts a range.
*   ``:0read file`` means put the file content above the first line of the file

*   ``:.,$write tempo`` means writing lines from the cursor until the end of the file into file tempo
*   ``:.write >>collection`` means appending the current line to the end of file collection

##### formatting text

*   ``gq`` format something like a paragraph(``qgap``)

##### changing case

*   ``gUw`` to make a word UPPERCASE
*   ``guw`` the opposite
*   ``g~w`` swap each case
*   ``gUU`` makes the whole line UPPERCASE
*   ``guu``, ``g~~`` the whole line

##### !

*   ``!5Gsort`` use the sort program, which will run on the first 5 lines.(cursor line is 1)
*   ``:read !ls`` will read the command output


#### 2021/1/25

##### Basic Recovery

*   ``vim -r help.txt``. Vim will read the swap file stored before the computer crashed
*   ``vim -r ""`` to read the swap file for a file without name

##### the location of swap file

*   ``vim -r`` to list swap files for files in the current directory

#### Clever tricks

##### Replacing in several files

*   example
    1.  vim *.cpp
    2.  qq
    3.  :%s/\<GetResp\>/GetAnswer/ge(e means not finding a match is not an error)
    4.  :wnext
    5.  q
    6.  999@q

> it will change all GetResp to GetAnswer in *.cpp files

##### Change

``:%s/\([^,]*\), \(.*\)/\2 \1``
*   ``:.,/^$/-1!sort`` means from the current line until the next empty line(^$)(one line above the empty line), then use sort
*   ``4;/...`` means from line 4 till match ... after line 4
*   ``4,/...`` means from line 4 till match ... after the cursor line

*   ``:g/^/m 0`` to reverse the file

*   ``gCTRL-G`` to count words

##### find man page

*   example ``stdio.h``, in normal mode, use ``K``, ``\K`` for the word under the cursor

*   ``:Man stdio`` will also display the man page for stdio
*   ``:runtime! ftplugin/man.vim`` to make the man page appear in a vim window

