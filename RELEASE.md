# Release steps
1. Bump VERSION constant
2. Generate changelog and update
```shell
CHANGELOG_GITHUB_TOKEN=<token> bundle exec rake changelog
```
3. Commit & push a new tag
4. Build and push to rubygems
```shell
gem build matrix_boost
gem push matrix_boost-x.y.z.gem
```
