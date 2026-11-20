**Кратко по файлам:**
* constants.h:
    Можно трогать, менять наследующие классы.
    Для добавления константы необходимо воспользоваться данной основой:

        class Name: public _Constant{
            public:
                Name(){name=string;}
                Var* F() override{
                    
                }
        };

    И добавить данную константу в список constants.


* operators.h
    
    Можно трогать, менять наследующие классы.
    
    Для добавления оператора необходимо воспользоваться данной основой:

        class Name : public Operator{
        public:
            Name(){oper = string;priority = int;is_unary = bool;}
            Var* F2(Var* a, Var* b) override{ // Бинарный оператор

            }
            Var* F1(Var* a) override{ // Унарный оператор

            }
        };

    И добавить данный оператор в список operators.


* functions.h

    Можно трогать, менять наследующие классы.

    Для добавления функции необходимо воспользоваться одной из основ:

        class Name:public Function{ // Для синтаксиса func(Var,Var)
            public:
                Name(){name = string;}
                Var* F(std::vector<Var*> args) override{

                }
        };

    ИЛИ

        class Name:public ExeFunction{ // Для синтаксиса func(Var){code}
        public:
            Name(){name=string;}
            void F(std::vector<_Operation*> args,std::vector<_Operation*> code) override{ 

            }
        };

    ИЛИ

        class Name:public TypeFunction{ // Для синтаксиса Var.func(Var)
            public:
                Name(){name=string;}
                Var* F(std::vector<Var*> args) override{

                }
        };
    
    И добавить получившийся класс в соответствующий vector(functions,exeFunctions, typeFunctions)

* parser.h
    Лучше не трогать, если не понимаешь, что делаешь.

* variable.h
    Лучше не трогать, если не понимаешь, что делаешь.


**Для справки**
* Не стоит мучаться с get_type(), это уже служебная функция. Если надо конкретное значение - лучше пользоваться To_Type, а для установки значения SetVar. 
* Конечно же, в большинстве случаев необходимо в начале функции использовать Var = GetVar(Var) для каждого входного параметра еще в начале функции. Исключениями будут циклы, оператор присваивания и т. д. и т. п.

**Какие функции стоит требовать извне или внутри программы**
* Внутри программы: To_Type(*variable.h*), SetVar(*variable.h*), GetVar(*variable.h*), Execute(*parser.h*), _Decode(*parser.h*)
* Извне: Execute(*parser.h*)

**Как запускать(скомпилированный файл)**
* Запускать через консоль стандартной командой(расположение файла).
* Если не указать никаких аргументов, откроется "Live версия", которую я старался сделать максимально похожей на аналогичную программу в Python.
* Если же указать расположение файла, то будет произведена попытка этот самый файл считать и исполнить.