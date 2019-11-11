pushd ..\
CALL git submodule foreach git status
git submodule foreach git pull origin master
PAUSE