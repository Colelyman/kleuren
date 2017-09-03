#!/bin/bash

# This script will automatically add documentation to the 
# gh-pages branch of kleuren. It is based off of the following
# gist: https://gist.github.com/vidavidorra/548ffbcdae99d752da02

# don't exit gracefully if anything fails
set -e

# create a clean working directory for this script
mkdir docs
cd docs

# get the current gh-pages branch
git clone -b gh-pages https://git@$GH_REPO_REF
cd $GH_REPO_NAME

# configure git
# set the push default to simple i.e. push only the current branch
git config --global push.defaul simple
git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

# clear out everything in the gh-pages branch
CURRENTCOMMIT=`git rev-parse HEAD`
git reset --hard `git rev-list HEAD | tail -n 1`
git reset --soft $CURRENTCOMMIT

# this is to allow filenames starting with an underscore to be 
# seen on the gh-pages site.
echo "" > .nojekyll

# generate the Doxygen code documentation!
echo "Generating the Doxygen code documentation..."
doxygen $DOXYFILE 2>&1 | tee doxygen.log

# check if Doxygen successfully create the documentation
if [ -d "html" ] && [ -f "html/index.html" ]; then
    echo "Uploading documentation to the gh-pages branch..."
    # add the files
    git add --all

    # commit the files with the Travis build number and the GitHub
    # commit reference
    git commit -m "Deplot code docs to GitHub Pages Travis build: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"

    # force push to the remove gh-pages branch
    git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1
else
    echo "" >&2
    echo "Warning: No documentation (html) files have been found!' >&2"
    echo "Warning: Not going to push the documentation to GitHub!" >&2
    exit 1
fi

