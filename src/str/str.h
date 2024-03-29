#ifndef AQUASENSE_STR
#define AQUASENSE_STR

/**
 * @brief      Functions seperates text into two variables by finding index of substring 
 *
 * @param      _text    The text
 * @param      _sub     The substring
 * @param      _first  	Variable that will contain first part 
 * @param      _second  Variable that will contain second part
 * 
 * @return     void
 */
void seperateTextWithSub(char* _text, char* _sub, char** _first, char** _second);

/**
 * @brief      Function that reads data from file
 *
 * @param[in]  _path  The file path
 *
 * @return     File data as char* (string)
 */
char* sReadDataFromFile(const char* _path);

/**
 * @brief      Returns path with separators based on OS
 *
 * @param[in]  count      The count
 * @param[in]  <unnamed>  va_args
 *
 * @return     path
 */
char* newPath(int count, ...);

#endif