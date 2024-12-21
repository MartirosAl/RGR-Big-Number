#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

enum class TokenType 
{
   LETTER,
   DIGIT,
   ARITHMETIC_OPERATION,
   RELATIONSHIP,
   SPACE,
   LF,
   END,
   SEMI_COLON,
   COMMENT,
   ERROR
};

enum States 
{ 
   A1, A2,
   B1, 
   C1, 
   D1, 
   E1, E2, E3,
   F1, F2, F3,
   G1,
   H1,
   I1, I2,
   J1,
   Stop 
};

enum Relation
{
   Equal,
   Not,
   Less,
   More,
   Not_equal,
   Less_or_equal,
   More_or_equal
};

struct SymbolicToken
{
   TokenType token_class; 
   int value;
   int number_line;
};

SymbolicToken Transliterator(int character)
{
   SymbolicToken result;
   result.value = 0;
   if (character >= 'A' && character <= 'Z' || character >= 'a' && character <= 'z')
   {
      result.token_class = TokenType::LETTER;
      result.value = character;
   }
   else if (character >= '0' && character <= '9')
   {
      result.token_class = TokenType::DIGIT;
      result.value = character - '0';
   }
   else if (character == '+' || character == '-' || character == '*' || character == '/')
   {
      result.token_class = TokenType::ARITHMETIC_OPERATION;
      result.value = character;
   }
   else if (character == '<')
   {
      result.token_class = TokenType::RELATIONSHIP;
      result.value = Less;
   }
   else if (character == '>')
   {
      result.token_class = TokenType::RELATIONSHIP;
      result.value = More;
   }
   else if (character == '=')
   {
      result.token_class = TokenType::RELATIONSHIP;
      result.value = Equal;
   }
   else if (character == '!')
   {
      result.token_class = TokenType::RELATIONSHIP;
      result.value = Not;
   }
   else if (character == ' ')
   {
      result.token_class = TokenType::SPACE;
      result.value = character;
   }
   else if (character == ';')
   {
      result.token_class = TokenType::SEMI_COLON;
      result.value = character;
   }
   else if (character == '\n')
   {
      result.token_class = TokenType::LF;
      result.value = character;
   }
   else if (character == EOF)
   {
      result.token_class = TokenType::END;
      result.value = character;
   }
   else
   {
      result.token_class = TokenType::ERROR;
      result.value = character;
   }
   return result;
}


template<typename T, typename U>
void Push_Back(T table_constants, const U register_number)
{
   Expansion(table_constants);
   table_constants[sizeof(table_constants) / sizeof(T)] = register_number;
}

template<typename T, typename U>
bool Find_In_Array(const T table_constants, const U register_number)
{
   if (table_constants == nullptr)
      return false;

   for (int i = 0; i < sizeof(table_constants) / sizeof(T); i++)
   {
      if (table_constants[i] == register_number)
         return true;
   }
   return false;
}

template<typename T>
void Expansion(T*& array)
{
   if (array == nullptr)
   {
      array = new T[1];
      return;
   }

   T* temp = new T[sizeof(array) / sizeof(T) + 1];

   for (int i = 0; i < (sizeof(array) / sizeof(T)); i++)
   {
      temp[i] = array[i];
   }
   delete[] array;

   array = temp;
}

//Процедура ДОБАВИТЬ_КОНСТАНТУ
void Add_Constant(bool flag_constant, int*& table_constants, int register_number, int*& register_indicator)
{
   if (flag_constant == 0)
      return;

   if (table_constants == nullptr)
   {
      Expansion(table_constants);
      table_constants[0] = register_number;
      register_indicator = &table_constants[0];
      return;
   }

   if (!Find_In_Array(table_constants, register_number))
   {
      Push_Back(table_constants, register_number);
   }

   register_indicator = &table_constants[sizeof(table_constants) / sizeof(int)];
}

//Процедура СОЗДАТЬ_ЛЕКСЕМУ
void Create_Token(TokenType register_type_token, int* register_indicator, int register_value, int register_relationship, int number_line)
{
   SymbolicToken result;
   result.number_line = number_line;
   result.token_class = 
   result.value = 
}


void Lexical_Analyzer(const char* filename)
{
   ifstream file(filename);
   if (!file)
   {
      cout << "Не удалось открыть файл " << filename << endl;
      return;
   }

   //Таблица констант для вывода
   int* table_constants = nullptr;

   //Регистр класса служит для хранения класса лексемы
   TokenType register_type_token;

   //Регистр указателя содержит указатель на таблицу имён для лексем PUSH и POP
   int* register_indicator = nullptr;

   //Регистр числа используется для вычисления констант
   int register_number;

   //Регистр отношения хранит информацию о первом символе отношения
   int register_relationship;

   //Регистр переменной накапливает имя переменной
   string register_variable;

   //Регистр обнаружения хранит номер позиции в таблице обнаружения для поиска ключевых слов
   int register_detection;

   //Регистр значения хранит значения лексем
   int register_value;

   //Номер строки хранит номер текущей строки в программе
   int number_line = 0;

   //Флаг константы равен 1, если была прочитана константа после ключевого слова push, и 0, если был прочитан номер строки после слова jmp или ji
   bool flag_constant;
   
   //Флаг остановки
   bool stop = 0;



   int state = A1;

   while (!stop)
   {
      int character = file.get();
      SymbolicToken token = Transliterator(character);

      switch (state)
      {

////////////////////////////////////////////////////////////////////////////A1
      case (A1):
         switch (token.token_class)
         {
         case (TokenType::LETTER)://B1a

            if (!register_indicator)
               Expansion(register_indicator);
            else
               Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = B1;
            break;

         case (TokenType::ARITHMETIC_OPERATION)://C1a
            
            register_type_token = TokenType::ARITHMETIC_OPERATION;
            register_value = token.value;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            
            state = C1;
            break;

         case (TokenType::RELATIONSHIP)://D1a

            register_type_token = TokenType::RELATIONSHIP;
            register_relationship = token.value;

            state = D1;
            break;

         case (TokenType::SPACE)://A1

            state = A1;
            break;

         case (TokenType::LF)://A1b

            number_line++;

            state = A1;
            break;

         case (TokenType::SEMI_COLON)://I1a

            register_type_token = TokenType::COMMENT;

            state = I1;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////A2
      case (A2):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://B1a

            if (!register_indicator)
               Expansion(register_indicator);
            else
               Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = B1;
            break;

         case (TokenType::ARITHMETIC_OPERATION)://C1a

            register_type_token = TokenType::ARITHMETIC_OPERATION;
            register_value = token.value;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = C1;
            break;

         case (TokenType::RELATIONSHIP)://D1a

            register_type_token = TokenType::RELATIONSHIP;
            register_relationship = token.value;

            state = D1;
            break;

         case (TokenType::SPACE)://A2

            state = A2;
            break;

         case (TokenType::LF)://A21

            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://I2a

            register_type_token = TokenType::COMMENT;

            state = I2;
            break;

         case (TokenType::END)://EXIT1

            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////B1
      case(B1):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://M1

            state = M1;//Обнаружение команд
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////C1
      case(C1):

         switch (token.token_class)
         {
         case (TokenType::SPACE)://C1

            state = C1;
            break;

         case (TokenType::LF)://A2a

            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://I2a

            register_type_token = TokenType::COMMENT;

            state = I2;
            break;

         case (TokenType::END)://EXIT1

            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////D1
      case (D1):

         switch (token.token_class)
         {
         case (TokenType::RELATIONSHIP)://C1h

            if (token.value != '=')
            {
               //ОШИБКА!!!
               state = Stop;
               break;
            }
            if (register_relationship >= Not && register_relationship <= More)
               register_relationship += 3;//Not + 3 = Not_equal, Less + 3 = Less_or_equal, More + 3 = More_or_equal
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = C1;
            break;

         case (TokenType::SPACE)://C1g

            if (register_relationship == Not)
               state = Stop;//ОШИБКА!!!
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = C1;
            break;

         case (TokenType::LF)://A2e

            if (register_relationship == Not)
               state = Stop;//ОШИБКА!!!
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://I2d

            if (register_relationship == Not)
               state = Stop;//ОШИБКА!!!
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::COMMENT;

            state = I2;
            break;

         case (TokenType::END)://EXIT2

            if (register_relationship == Not)
               state = Stop;//ОШИБКА!!!
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////E1
      case (E1):

         switch (token.token_class)
         {
         case (TokenType::SPACE)://F1

            state = F1;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////E1
      case (E2):

         switch (token.token_class)
         {
         case (TokenType::SPACE)://F2

            state = F2;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////E3
      case (E3):

         switch (token.token_class)
         {
         case (TokenType::SPACE)://F3

            state = F3;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////F1
      case(F1):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://H1a

            register_variable = token.value;

            state = H1;
            break;

         case (TokenType::DIGIT)://G1a

            register_number = token.value;

            state = G1;
            break;

         case (TokenType::SPACE)://F1

            state = F1;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////F2
      case(F2):

         switch (token.token_class)
         {
         case (TokenType::DIGIT)://G1a

            register_number = token.value;

            state = G1;
            break;

         case (TokenType::SPACE)://F2

            state = F2;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////F3
      case(F3):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://H1a

            register_variable = token.value;

            state = H1;
            break;

         case (TokenType::SPACE)://F3

            state = F3;
            break;

         case (TokenType::LF)://A2f

            register_type_token = TokenType::ERROR;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////G1
      case(G1):

         switch (token.token_class)
         {
         case (TokenType::DIGIT)://G1b
            
            register_number *= 10;
            register_number += token.value;

            state = G1;
            break;

         case (TokenType::SPACE)://C1e

            Add_Constant(flag_constant, table_constants, register_number, register_indicator);

            state = C1;
            break;

         case (TokenType::LF)://A2c

            Add_Constant(flag_constant, table_constants, register_number, register_indicator);
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://I2b

            Add_Constant(flag_constant, table_constants, register_number, register_indicator);
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::COMMENT;

            state = I2;
            break;

         case (TokenType::END)://EXIT3

            Add_Constant(flag_constant, table_constants, register_number, register_indicator);
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////H1
      case(H1):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://H1b

            register_variable.push_back(token.value);

            state = H1;
            break;

         case (TokenType::DIGIT)://H1b

            register_variable.push_back(token.value);

            state = H1;
            break;

         case (TokenType::SPACE)://C1f

            Добавить переменную;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = C1;
            break;

         case (TokenType::LF)://A2d
            
            Добавить переменную;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://I2c

            Добавить переменную;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::COMMENT;

            state = I2;
            break;

         case (TokenType::END)://EXIT4

            Добавить переменную;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////I1
      case(I1):

         switch (token.token_class)
         {

         case (TokenType::LETTER)://I1

            state = I1;
            break;

         case (TokenType::DIGIT)://I1

            state = I1;
            break;

         case (TokenType::ARITHMETIC_OPERATION)://I1

            state = I1;
            break;
            
         case (TokenType::RELATIONSHIP)://I1

            state = I1;
            break;

         case (TokenType::SPACE)://I1

            state = I1;
            break;

         case (TokenType::LF)://A1a

            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A1;
            break;

         case(TokenType::SEMI_COLON)://I1

            state = I1;
            break;

         case (TokenType::ERROR)://I1

            state = I1;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////I1
      case(I2):

         switch (token.token_class)
         {
         case(TokenType::LETTER)://I2

            state = I2;
            break;

         case(TokenType::DIGIT)://I2

            state = I2;
            break;

         case(TokenType::ARITHMETIC_OPERATION)://I2

            state = I2;
            break;

         case(TokenType::RELATIONSHIP)://I2

            state = I2;
            break;

         case(TokenType::SPACE)://I2

            state = I2;
            break;

         case(TokenType::LF)://A2b

            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);
            number_line++;

            state = A2;
            break;

         case(TokenType::SEMI_COLON)://I2

            state = I2;
            break;

         case(TokenType::ERROR)://I2

            state = I2;
            break;

         case(TokenType::END)://EXIT1

            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }

////////////////////////////////////////////////////////////////////////////I1
      case(J1):

         switch (token.token_class)
         {
         case (TokenType::LETTER)://J1

            state = J1;
            break;

         case (TokenType::DIGIT)://J1

            state = J1;
            break;

         case (TokenType::ARITHMETIC_OPERATION)://J1

            state = J1;
            break;

         case (TokenType::RELATIONSHIP)://J1

            state = J1;
            break;

         case (TokenType::SPACE)://J1

            state = J1;
            break;

         case (TokenType::LF)://A2a

            number_line++;

            state = A2;
            break;

         case (TokenType::SEMI_COLON)://J1

            state = J1;
            break;

         case (TokenType::ERROR)://J1

            state = J1;
            break;

         case (TokenType::END)://EXIT1

            register_type_token = TokenType::END;
            Create_Token(register_type_token, register_indicator, register_value, register_relationship, number_line);

            state = Stop;
            break;

         default:
            state = Stop;
            break;
         }


      default:
         state = Stop;
         break;
      }

   }
};
