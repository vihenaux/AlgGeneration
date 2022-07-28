git checkout main
git pull
git merge $1
git push
git push --delete origin $1
git branch -d $1