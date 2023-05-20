# Генератор пароля

### Системные требования
  - *Процессор*: Intel 3-го поколения / AMD Ryzen или новее. <br>
  - *Операционная система*: Windows 10 или новее.
  - *Дополнительное програмное обеспечение*: Windows Subsystem for Linux.

### Выполнено
1. Проверка наличия процессорной инструкции *RdRand*
2. Генерация сида при помощи *RdRand*
3. Генерация криптографически защищенных случайных байтов при помощи алгоритма *Fortuna* 
4. Перевод байтов в *UTF-8* символы 
5. ...

### Структура программы
```mermaid
graph

A_RUN[Запуск]
A_A[Получение параметров генерации]
A_B[Запуск консольного приложения с параметрами генерации]
A[Проверка наличия инструкции]
B[Генерация сида]
C[Генерация случайных байтов вида FF]
D[Обработка в обрабатываемый формат данных вида 0xFF]
E[Конвертация байтов в символы UTF-8]
F[Отправка сгенерированного пароля]
G[Вывод пароля]
H[Выход из приложения]
Z[Выход из программы]

subgraph P[СТРУКТУРА ПРОГРАММЫ]
    subgraph PWGEN[Генератор пароля];
        A_RUN-->A_A;
        subgraph PROGRAM[Графическое приложение]
            A_A-->H;
            A_A-->A_B;
            A_B-->A;
            F-->G;
            G-->H;
            G-->A_A;
            subgraph TERMINAL[Консольная программа]
                A-->|Не доступна|Z;
                E-->F;
                F-->Z;
                subgraph RDRAND[Процессорная инструкция RdRand]
                    A-->|Доступна|B;
                end
                subgraph CSPRNG[Генератор Fortuna]
                    B-->C;
                end
                subgraph UTF-8[Обработка вывода программы]
                    direction TB
                    C-->D;
                    D-->E;
                end
            end 
        end   
    end
end
```
