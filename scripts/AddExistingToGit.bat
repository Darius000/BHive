pushd ..\
ECHO "# BHive" >> README.md
CALL git remote add origin https://github.com/Darius000/BHive.git
CALL git push -u origin master
popd