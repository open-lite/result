#pragma once

#define RESULT_VERIFY_UNSCOPED(fn, var) \
auto var = fn; \
if(!var.has_value()) return var.error();


#define RESULT_TRY_MOVE_UNSCOPED(lhs, rhs, var) \
RESULT_VERIFY_UNSCOPED(rhs, var) \
lhs = *std::move(var);

#define RESULT_TRY_COPY_UNSCOPED(lhs, rhs, var) \
RESULT_VERIFY_UNSCOPED(rhs, var) \
lhs = *var;



#define RESULT_VERIFY(fn) \
{ RESULT_VERIFY_UNSCOPED(fn, r) }


#define RESULT_TRY_MOVE(lhs, rhs) \
{ RESULT_TRY_MOVE_UNSCOPED(lhs, rhs, r) } 

#define RESULT_TRY_COPY(lhs, rhs) \
{ RESULT_TRY_COPY_UNSCOPED(lhs, rhs, r) } 



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