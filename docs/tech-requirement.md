# Техническое задание

- **Функциональность проекта:** 
    1. Создание пароля из неограниченного количества символов.
    2. Возможность выбирать какие символы необходимо использовать при создании пароля.
    3. Генерация пароля проводится с использованием криптографически стойкого генератора чисел Fortuna.

- **Формат входных данных:** 
  Входные данные включают в себя выбор длины генерируемого пароля и параметров генерации пароля, таких как длина пароля и используемые типы символов при генерации.

- **Интерфейс приложения:** 
  Приложение Password Generator – консольное приложение, взаимодействие с которым осуществляется через отправку параметров в терминал.

- **Аргументы командной строки:** 
  Приложение не принимает аргументы командной строки.

- **Чтение исходных данных извне программы:** 
  Приложение не использует чтение исходных данных извне программы. Все параметры генерации пароля указываются непосредственно при работе приложения.