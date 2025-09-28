#ifndef RussianSymbols_h
#define RussianSymbols_h

#include <Arduino.h>

// =============================================================================
// RussianSymbols.h
// Библиотека кастомных символов русского алфавита для LCD дисплеев
// =============================================================================

/**
 * @file RussianSymbols.h
 * @brief Библиотека кастомных символов русского алфавита для LCD дисплеев
 * @version 1.0
 * @date 2024
 * 
 * Содержит bitmap-данные для создания русских букв на LCD 1602 и других дисплеях.
 * Все символы имеют размер 5x8 пикселей.
 */

// =============================================================================
// Структура с кастомными символами русских букв
// =============================================================================

struct RussianSymbols {
  // Заглавные буквы
  static const byte A_RU[8];      ///< Русская буква А
  static const byte B_RU[8];      ///< Русская буква Б
  static const byte V_RU[8];      ///< Русская буква В
  static const byte G_RU[8];      ///< Русская буква Г
  static const byte D_RU[8];      ///< Русская буква Д
  static const byte E_RU[8];      ///< Русская буква Ё
  static const byte EE_RU[8];     ///< Русская буква Е
  static const byte ZH_RU[8];     ///< Русская буква Ж
  static const byte Z_RU[8];      ///< Русская буква З
  static const byte I_RU[8];      ///< Русская буква И
  static const byte II_RU[8];     ///< Русская буква Й
  static const byte K_RU[8];      ///< Русская буква К
  static const byte L_RU[8];      ///< Русская буква Л
  static const byte M_RU[8];      ///< Русская буква М
  static const byte N_RU[8];      ///< Русская буква Н
  static const byte O_RU[8];      ///< Русская буква О
  static const byte P_RU[8];      ///< Русская буква П
  static const byte R_RU[8];      ///< Русская буква Р
  static const byte S_RU[8];      ///< Русская буква С
  static const byte T_RU[8];      ///< Русская буква Т
  static const byte U_RU[8];      ///< Русская буква У
  static const byte F_RU[8];      ///< Русская буква Ф
  static const byte H_RU[8];      ///< Русская буква Х
  static const byte C_RU[8];      ///< Русская буква Ц
  static const byte CH_RU[8];     ///< Русская буква Ч
  static const byte SH_RU[8];     ///< Русская буква Ш
  static const byte SHH_RU[8];    ///< Русская буква Щ
  static const byte TV_RU[8];     ///< Русская буква Ъ
  static const byte Y_RU[8];      ///< Русская буква Ы
  static const byte MY_RU[8];     ///< Русская буква Ь
  static const byte EEE_RU[8];    ///< Русская буква Э
  static const byte UU_RU[8];     ///< Русская буква Ю
  static const byte YA_RU[8];     ///< Русская буква Я

  // Строчные буквы (опционально, можно добавить позже)
  // static const byte a_ru[8];    ///< Русская буква а
  // static const byte b_ru[8];    ///< Русская буква б
  // и т.д.

  // Специальные символы
  static const byte QUESTION_RU[8];  ///< Вопросительный знак (русский стиль)
  static const byte EXCLAMATION_RU[8]; ///< Восклицательный знак (русский стиль)
};

// =============================================================================
// Дополнительные утилиты для работы с символами
// =============================================================================

/**
 * @struct SymbolData
 * @brief Данные символа и его метаинформация
 */
struct SymbolData {
  const byte* data;        ///< Указатель на bitmap данные
  const char* name;        ///< Название символа (латиница)
  const char* cyrillic;    ///< Кириллическое представление
  uint8_t width;           ///< Ширина символа в пикселях
  uint8_t height;          ///< Высота символа в пикселях
};

/**
 * @class SymbolManager
 * @brief Менеджер для работы с кастомными символами
 */
class SymbolManager {
public:
  /**
   * @brief Получить данные символа по его кириллическому представлению
   * @param cyrillicChar кириллический символ
   * @return структура SymbolData с данными символа
   */
  static SymbolData getSymbolData(const char* cyrillicChar);
  
  /**
   * @brief Получить количество доступных символов
   * @return количество символов
   */
  static uint8_t getSymbolsCount();
  
  /**
   * @brief Проверить, является ли символ русской буквой
   * @param c символ для проверки
   * @return true если символ - русская буква
   */
  static bool isCyrillic(char c);
  
  /**
   * @brief Получить индекс символа в таблице
   * @param cyrillicChar кириллический символ
   * @return индекс символа или 255 если не найден
   */
  static uint8_t getSymbolIndex(const char* cyrillicChar);
};

// =============================================================================
// Константы для работы с символами
// =============================================================================

// Максимальное количество кастомных символов
const uint8_t MAX_CUSTOM_SYMBOLS = 33;

// Размер символа в байтах
const uint8_t SYMBOL_SIZE_BYTES = 8;

// =============================================================================
// Вспомогательные макросы для создания символов
// =============================================================================

/**
 * @macro CREATE_SYMBOL
 * @brief Макрос для удобного создания bitmap символа
 */
#define CREATE_SYMBOL(b0, b1, b2, b3, b4, b5, b6, b7) \
  { b0, b1, b2, b3, b4, b5, b6, b7 }

/**
 * @macro EMPTY_SYMBOL
 * @brief Пустой символ (все пиксели выключены)
 */
#define EMPTY_SYMBOL CREATE_SYMBOL(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/**
 * @macro FULL_SYMBOL
 * @brief Полностью заполненный символ (все пиксели включены)
 */
#define FULL_SYMBOL CREATE_SYMBOL(0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F)

#endif // RussianSymbols_h