#ifndef H_782A772873A84586A0984C5D256F68FF
#define H_782A772873A84586A0984C5D256F68FF

template <typename T>
struct is_vector_container : std::false_type
{
};

template <typename T, typename A>
struct is_vector_container<std::vector<T, A>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_vector_container_v = is_vector_container<T>::value;

#endif // H_782A772873A84586A0984C5D256F68FF


