#include "file_check.h"


mild_bool check_file_with_mode(
    mild_cstr                   pathname__,
    mild_i32                    mode__
    )
{
    if( mild_null == pathname__ )
        return mild_false;

    if( -1 == access( pathname__, mode__ ) )
        return mild_false;

    return mild_true;
}


mild_bool checkFileExist(
    mild_cstr                   pathname__
    )
{
    return check_file_with_mode( pathname__, F_OK );
}


mild_bool checkFileReadPerm(
    mild_cstr                   pathname__
    )
{
    return check_file_with_mode( pathname__, R_OK );
}
