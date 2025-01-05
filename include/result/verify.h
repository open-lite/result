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