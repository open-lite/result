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




#define RESULT_VERIFY_UNSCOPED_CAST_ERR(fn, var, err_type) \
auto var = fn; \
if(!var.has_value()) return static_cast<err_type>(var.error()); \

#define RESULT_TRY_MOVE_UNSCOPED_CAST_ERR(lhs, rhs, var, err_type) \
RESULT_VERIFY_UNSCOPED_CAST_ERR(rhs, var, err_type) \
lhs = *std::move(var);

#define RESULT_TRY_COPY_UNSCOPED_CAST_ERR(lhs, rhs, var) \
RESULT_VERIFY_UNSCOPED_CAST_ERR(rhs, var, err_type) \
lhs = *var;



#define RESULT_VERIFY_CAST_ERR(fn, err_type) \
{ RESULT_VERIFY_UNSCOPED_CAST_ERR(fn, r, err_type) }


#define RESULT_TRY_MOVE_CAST_ERR(lhs, rhs, err_type) \
{ RESULT_TRY_MOVE_UNSCOPED_CAST_ERR(lhs, rhs, r, err_type) } 

#define RESULT_TRY_COPY_CAST_ERR(lhs, rhs, err_type) \
{ RESULT_TRY_COPY_UNSCOPED_CAST_ERR(lhs, rhs, r, err_type) }
