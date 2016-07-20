#!/bin/sh
REPO_PATH=github.com/bvanderlaan/Taranis.git
DOCS_PATH=gh-pages/docs
HTML_PATH=build/doc/html
COMMIT_USER="Documentation Builder"
COMMIT_EMAIL="brad.vanderlaan@gmail.com"

# Only update docs on master branch.
if [ ${TRAVIS_BRANCH} != "master" ]; then exit 0; fi

# Only update docs for the first or only build job. This way we are not updating the docs 
# multiple times on a matrix configuration.
BUILD_JOB_SEP_POS=$(expr index ${TRAVIS_JOB_NUMBER} .)
if [ ${BUILD_JOB_SEP_POS} > 0 ] && [ ${TRAVIS_JOB_NUMBER:${BUILD_JOB_SEP_POS}} > 1 ]; then exit 0; fi

# Exit with nonzero exit code if anything fails
set -e

echo 'Uploading documentation to the gh-pages branch...'

# Checkout and clean out the docs folder
git clone -b gh-pages https://${REPO_PATH} --single-branch gh-pages
cd "${DOCS_PATH}"
git rm -rf .
cd -

if [ -d "${HTML_PATH}" ]; then
    # copy the newly created documents into the gh-pages docs folder.
    cp -R "${HTML_PATH}" "${DOCS_PATH}"

    # commit the new documentation
    cd ${DOCS_PATH}
    git add --all
    git config user.name "${COMMIT_USER}"
    git config user.email "${COMMIT_EMAIL}"
    git commit -m"Automated documentation build for changeset ${TRAVIS_COMMIT}"
    git push --force "https://${GH_REPO_TOKEN}@${REPO_PATH}" > /dev/null 2>&1
    cd -
else
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1
fi