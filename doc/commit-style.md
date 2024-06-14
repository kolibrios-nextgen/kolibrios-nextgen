# Commit style

Commit style accepted in __KolibriOS-NG__ project

## Overview

The project accepts commit standard for transparency and comprehension of the changes being made. The acceptable commit style is described below

## Naming

### Initial commits

Initial commit message should be written in the following style:

```text
Initial commit
```

### Regular commits

- Pattern

  Regular commit message should consist of several parts and be built according to the following template:

  ```test
  Category: Commit message body

  Long description if necessary
  ```

  Commit message body and description should briefly reflect the meaning of the commit changes

  Commit message body should be written starting with a capital letter

  Description should be separated from the body by one empty line

- Length

  Commonly accepted 50/72 rule is used to format commits. 50 is the maximum number of characters of the commit title and 72 is the maximum character length of the commit body

- Categories

  List of existing categories accepted in the project:

  - `Krn` - kernel
  - `Drv` - drivers
  - `Libs` - libraries
  - `Skins` - skins
  - `Build` - build system
  - `CI/CD` - CI/CD
  - `Docs` - documentation
  
  List of categories for exceptional situations:
  
  - `All` - global changes
  - `Other` - unclassifiable changes

  If changes are made to a specific component, the name of the component separated by `/` character needs to be specified. For example:

  ```text
  Apps/shell
  Libs/libimg
  ```

### Merge commits

Merge commits are __prohibited__ in the project

### Unwanted commits

Commit messages like `Refactoring`/`Update files` are __unwanted__ in the project

## Signing

This is not a requirement, but it is strongly recommended to sign commits. This can be done by the following command:

```sh
git commit -s
```
