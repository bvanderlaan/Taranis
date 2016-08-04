#!/bin/sh
REPO_PATH=github.com/bvanderlaan/Taranis.git
DOCS_PATH=gh-pages/docs
HTML_PATH=build/doc/html
COMMIT_USER="Documentation Builder"
COMMIT_EMAIL="brad.vanderlaan@gmail.com"

# Only update docs on master branch.
if [ ${TRAVIS_BRANCH} != "master" ]; then exit 0; fi

# Below we ensure that we only publish for the second build job. The second build
# job is on OSX and the OSX machine on Travis-CI has Doxygen 1.8.11 where as the Linux
# machines is only on Doxygen 1.8.6. The later verison of Doxygen ignores the markdown badge
# links in the Readme.md file as image tags with anchors does not seem to be supported in 
# Doxygen Markdown. In 1.8.6 they still get shown as a link but the link text is the markdown
# for an image which is quite ugly. Using 1.8.11 does not give me the badges but at least the
# resulting HTML is prettier.

# Only update docs for the second build job. This way we are not updating the docs 
# multiple times on a matrix configuration.
if [ ${TRAVIS_JOB_NUMBER#*.} -ne 2 ]; then exit 0; fi

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