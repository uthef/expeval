// CHARACTER MATCHING
#define IS_SPACE_CHAR(c) (c == '\n' || c == ' ' || c == '\t' || c == '\r')
#define IS_NUMERIC_CHAR(c) (c >= '0' && c <= '9')
#define IS_NAME_CHAR(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
#define IS_OPERATOR_CHAR(c) (c == '+' || c == '-' || c == '/' || c == '*')

// FLAG OPERATIONS
#define IS_FLAG_SET(x, y) (x & y) == y
#define IS_FLAG_NOT_SET(x, y) (x & y) != y
