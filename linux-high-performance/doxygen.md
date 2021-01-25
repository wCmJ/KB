1. install
    - ./configure –prefix=/home/user1/bin
    - make
    - make install

2. Usage
    - 生成配置文件
        - doxygen -g / doxygen -g user-defined-filename
    - 编辑配置文件
        - <OUTPUT_DIRECTORY> = /home/user1/documentation    输出目录
        - <INPUT> = /home/user1/project/kernel              输入
        - <RECURSIVE> = YES                                 是否递归搜索整个目录
        - <EXTRACT_ALL> = YES                               即使各个类或函数没有文档，也要提取信息
        - <EXTRACT_PRIVATE> = YES                           提取私有数据成员
        - <EXTRACT_STATIC> = YES                            提取文件的静态成员
        - <FILE_PATTERNS> = *.cc \
                            *.cxx \
                            *.cpp \
                            *.c++ \
                            *.java \
                            *.ii \
                            *.ixx \
                            *.ipp \
                            *.i++ \
                            *.inl \
                            *.idl \
                            *.ddl \
                            *.odl \
                            *.h \
                            *.hh \
                            *.hxx \
                            *.hpp \
                            *.h++ \
                            *.cs \
                            *.d \
                            *.php \
                            *.php4 \
                            *.php5 \
                            *.phtml \
                            *.inc \
                            *.m \
                            *.markdown \
                            *.md \
                            *.mm \
                            *.dox \
                            *.doc \
                            *.txt \
                            *.py \
                            *.pyw \
                            *.f90 \
                            *.f95 \
                            *.f03 \
                            *.f08 \
                            *.f18 \
                            *.f \
                            *.for \
                            *.vhd \
                            *.vhdl \
                            *.ucf \
                            *.qsf \
                            *.ice
    - 运行
        - doxygen Doxyfile
    
    -输出
        - html
        - UNIX手册页，需把<GENERATE_MAN> = YES
        - Rich Text Format（RTF）：<GENERATE_RTF> = YES
        - Latex：<GENERATE_LATEX> = YES，<LATEX_OUTPUT> = Latex
        - Microsoft® Compiled HTML Help（CHM）：<GENERATE_HTMLHELP> = YES
        - Extensible Markup Language（XML）：<GENERATE_XML> = YES


        