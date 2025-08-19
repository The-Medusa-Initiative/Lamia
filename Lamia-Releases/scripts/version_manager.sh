#!/bin/bash
# Lamia Version Manager v0.3.0

CURRENT_VERSION="0.3.0"

bump_version() {
    local type=$1
    local version=$CURRENT_VERSION
    
    IFS='.' read -ra PARTS <<< "$version"
    major=${PARTS[0]}
    minor=${PARTS[1]}
    patch=${PARTS[2]}
    
    case $type in
        major)
            major=$((major + 1))
            minor=0
            patch=0
            ;;
        minor)
            minor=$((minor + 1))
            patch=0
            ;;
        patch)
            patch=$((patch + 1))
            ;;
    esac
    
    echo "$major.$minor.$patch"
}

if [ "$1" = "--bump" ]; then
    NEW_VERSION=$(bump_version $2)
    echo "$NEW_VERSION" > VERSION
    echo "Version bumped to: $NEW_VERSION"
else
    echo "Current version: $CURRENT_VERSION"
    echo "Usage: $0 --bump <major|minor|patch>"
fi
