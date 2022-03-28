# ifndef USER_INCLUDES_INCLUDED
# define USER_INCLUDES_INCLUDED


# ifndef NO_DATA_SERIALIZATION
# include "../dataclass/Data.cpp"
# endif /* NO_DATA_SERIALIZATION */
# include "../dataclass/Point.cpp"
# include "../dataclass/Array.cpp"
template<typename T>
using ArrayP = Array<Point<T>>;
# include "../algorithms/generate.cpp"
# include "../algorithms/formulas.cpp"


# endif /* USER_INCLUDES_INCLUDED */
