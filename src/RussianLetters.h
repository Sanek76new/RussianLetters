#ifndef RussianLetters_h
#define RussianLetters_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =============================================================================
// Структура с кастомными символами русских букв
// =============================================================================

struct RussianSymbols {
  // Статические массивы с данными символов (определены в .cpp файле)
  static const byte A_RU[8];      // А
  static const byte B_RU[8];      // Б
  static const byte V_RU[8];      // В
  static const byte G_RU[8];      // Г
  static const byte D_RU[8];      // Д
  static const byte E_RU[8];      // Ё
  static const byte EE_RU[8];     // Е
  static const byte ZH_RU[8];     // Ж
  static const byte Z_RU[8];      // З
  static const byte I_RU[8];      // И
  static const byte II_RU[8];     // Й
  static const byte K_RU[8];      // К
  static const byte L_RU[8];      // Л
  static const byte M_RU[8];      // М
  static const byte N_RU[8];      // Н
  static const byte O_RU[8];      // О
  static const byte P_RU[8];      // П
  static const byte R_RU[8];      // Р
  static const byte S_RU[8];      // С
  static const byte T_RU[8];      // Т
  static const byte U_RU[8];      // У
  static const byte F_RU[8];      // Ф
  static const byte H_RU[8];      // Х
  static const byte C_RU[8];      // Ц
  static const byte CH_RU[8];     // Ч
  static const byte SH_RU[8];     // Ш
  static const byte SHH_RU[8];    // Щ
  static const byte TV_RU[8];     // Ъ
  static const byte Y_RU[8];      // Ы
  static const byte MY_RU[8];     // Ь
  static const byte EEE_RU[8];    // Э
  static const byte UU_RU[8];     // Ю
  static const byte YA_RU[8];     // Я
};

// =============================================================================
// Основной класс библиотеки - RussianLCD
// =============================================================================

class RussianLCD : public LiquidCrystal_I2C {
public:
  /**
   * Конструктор
   * @param lcd_addr I2C адрес дисплея
   * @param lcd_cols количество столбцов
   * @param lcd_rows количество строк
   */
  RussianLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
  
  /**
   * Инициализация дисплея (аналог begin() из LiquidCrystal_I2C)
   */
  void begin();
  
  /**
   * Инициализация дисплея с указанием размеров
   * @param cols количество столбцов
   * @param rows количество строк
   */
  void begin(uint8_t cols, uint8_t rows);
  
  /**
   * Переопределенный метод write для обработки русских символов
   * @param value байт для записи
   * @return количество записанных байт
   */
  virtual size_t write(uint8_t value);
  
  /**
   * Вывод русской строки на дисплей
   * @param str строка в кодировке UTF-8
   */
  void printRussian(const char* str);
  
  /**
   * Вывод русской строки на дисплей (версия для unsigned char)
   * @param str строка в кодировке UTF-8
   */
  void printRussian(const unsigned char* str);
  
  /**
   * Установка курсора с поддержкой русских символов
   * @param col столбец (0-based)
   * @param row строка (0-based)
   */
  void setCursorRU(uint8_t col, uint8_t row);
  
  /**
   * Очистка дисплея с поддержкой русских символов
   */
  void clearRU();

private:
  uint8_t utf8_state;           // Текущее состояние автомата UTF-8
  uint8_t current_byte1;        // Первый байт UTF-8 последовательности
  uint8_t loaded_symbols[8];    // Индексы загруженных символов (0xFF = пусто)
  uint8_t next_slot;            // Следующий слот для загрузки символа
  
  /**
   * Предзагрузка наиболее частых русских символов
   */
  void preloadCommonSymbols();
  
  /**
   * Поиск символа в кэше загруженных символов
   * @param byte1 первый байт UTF-8
   * @param byte2 второй байт UTF-8
   * @return индекс слота CGRAM или 0xFF если не найден
   */
  uint8_t findSymbolInCache(uint8_t byte1, uint8_t byte2);
  
  /**
   * Загрузка нового символа в CGRAM
   * @param symbol_index индекс символа в таблице
   * @return индекс слота CGRAM куда загружен символ
   */
  uint8_t loadNewSymbol(uint8_t symbol_index);
  
  /**
   * Загрузка символа в указанный слот CGRAM
   * @param slot слот CGRAM (0-7)
   * @param symbol_data указатель на данные символа
   */
  void loadSymbol(uint8_t slot, const byte* symbol_data);
};

// =============================================================================
// Упрощенный класс для начинающих - SimpleRussianLCD
// =============================================================================

class SimpleRussianLCD : public LiquidCrystal_I2C {
public:
  /**
   * Конструктор упрощенной версии
   * @param lcd_addr I2C адрес дисплея
   * @param lcd_cols количество столбцов
   * @param lcd_rows количество строк
   */
  SimpleRussianLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
  
  /**
   * Инициализация дисплея с предзагрузкой русских символов
   */
  void begin();
  
  /**
   * Вывод русской строки (упрощенная версия)
   * Поддерживает только основные 8 букв: А, Е, И, Н, О, Р, С, Т
   * @param str строка для вывода
   */
  void printRU(const char* str);
  
  /**
   * Установка курсора
   * @param col столбец (0-based)
   * @param row строка (0-based)
   */
  void setCursorRU(uint8_t col, uint8_t row);

private:
  /**
   * Загрузка русских символов в CGRAM
   */
  void loadRussianSymbols();
};

// =============================================================================
// Вспомогательные функции для работы с русскими символами
// =============================================================================

/**
 * Функция преобразования UTF-8 строки в последовательность для LCD
 * @param source исходная строка в UTF-8
 * @return преобразованная строка
 */
String utf8rus(String source);

/**
 * Функция проверки поддержки русского языка дисплеем
 * @return true если дисплей поддерживает русские символы
 */
bool isRussianSupported();

/**
 * Функция получения версии библиотеки
 * @return строка с версией библиотеки
 */
String getRussianLettersVersion();

// =============================================================================
// Совместимость с разными дисплеями
// =============================================================================

#ifdef USE_LCD2004
  #define RUSSIAN_LCD_COLS 20
  #define RUSSIAN_LCD_ROWS 4
#else
  #define RUSSIAN_LCD_COLS 16
  #define RUSSIAN_LCD_ROWS 2
#endif

// Макросы для быстрого создания экземпляров
#define CREATE_RUSSIAN_LCD(addr) RussianLCD lcd(addr, RUSSIAN_LCD_COLS, RUSSIAN_LCD_ROWS)
#define CREATE_SIMPLE_RUSSIAN_LCD(addr) SimpleRussianLCD lcd(addr, RUSSIAN_LCD_COLS, RUSSIAN_LCD_ROWS)

#endif // RussianLetters_h