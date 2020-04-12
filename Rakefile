require "bundler/gem_tasks"
require "rake/testtask"
require "matrix_boost/version"
require "github_changelog_generator/task"

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList["test/**/*_test.rb"]
end

task :compile do
  puts "Compiling extension"
  `cd ext && make clean`
  `cd ext && ruby extconf.rb`
  `cd ext && make`
  puts "Done"
end

GitHubChangelogGenerator::RakeTask.new :changelog do |config|
  config.user = "Bajena"
  config.project = "matrix_boost"
  config.future_release = "v#{MatrixBoost::VERSION}"
end

task :default => :test
