pushd ..\
ECHO "# BHive" >> README.md
CALL git init
CALL git add *
CALL git commit -m "first commit"
CALL git remote add origin https://github.com/Darius000/BHive.git
CALL git push -u origin master
popd
PAUSE