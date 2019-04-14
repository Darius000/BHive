set/p folder=
set/p module=
CALL git submodule add %module% %folder%
CALL git submodule init
CALL git submodule update