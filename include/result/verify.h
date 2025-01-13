#pragma once


#define RESULT_VERIFY(fn) \
{ \
auto r = fn; \
if(!r.has_value()) return r.error(); \
}


#define RESULT_TRY_MOVE(lhs, rhs) \
{ \
auto r = rhs; \
if(!r.has_value()) return r.error(); \
lhs = *std::move(r); \
} 

#define RESULT_TRY_COPY(lhs, rhs) \
{ \
auto r = rhs; \
if(!r.has_value()) return r.error(); \
lhs = *r; \
} 



#define RESULT_CAST_VERIFY(fn, err_type) \
{ \
auto r = fn; \
if(!r.has_value()) return static_cast<err_type>(r.error()); \
}


#define RESULT_CAST_TRY_MOVE(lhs, rhs, err_type) \
{ \
auto r = rhs; \
if(!r.has_value()) return static_cast<err_type>(r.error()); \
lhs = *std::move(r); \
} 

#define RESULT_CAST_TRY_COPY(lhs, rhs, err_type) \
{ \
auto r = rhs; \
if(!r.has_value()) return static_cast<err_type>(r.error()); \
lhs = *r; \
} 