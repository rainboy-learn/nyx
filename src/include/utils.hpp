#pragma once

template<typename T,typename... ts>
bool anyone(T c,ts... tt){
    return ((c == tt) || ...);
}
