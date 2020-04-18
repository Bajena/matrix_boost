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

task :benchmark_multiply do
  require "matrix_boost"

  dim = 4
  n = 10000

  m1 = Matrix.build(dim) { rand }
  m2 = Matrix.build(dim) { rand }

  puts "Benchmark multiplication (dim = #{dim}, n = #{n})..."

  Benchmark.benchmark(Benchmark::CAPTION, 45, Benchmark::FORMAT, ">Ruby slower (%):") do |x|
    r = x.report("Ruby matrix multiply:") { n.times { m1 * m2 } }
    c = x.report("C matrix multiply:") { n.times { MatrixBoost.multiply(m1, m2) } }

    MatrixBoost.apply_core_extensions
    x.report("Ruby matrix multiply after monkey patch:") { n.times { m1 * m2 } }

    [r / c]
  end

  puts "Done"
  puts ""
end

task :benchmark_inverse do
  require "matrix_boost"

  dim = 4
  n = 10000

  puts "Benchmark inversion (dim = #{dim}, n = #{n})..."

  m = Matrix.build(dim) { rand }

  Benchmark.benchmark(Benchmark::CAPTION, 45, Benchmark::FORMAT, ">Ruby slower (%):") do |x|
    r = x.report("Ruby matrix inverse:") { n.times { m.inverse } }
    c = x.report("C matrix inverse:") { n.times { MatrixBoost.invert(m) } }

    MatrixBoost.apply_core_extensions
    x.report("Ruby matrix inverse after monkey patch:") { n.times { m.inverse } }

    [r / c]
  end

  puts "Done"
  puts ""
end

GitHubChangelogGenerator::RakeTask.new :changelog do |config|
  config.user = "Bajena"
  config.project = "matrix_boost"
  config.future_release = "v#{MatrixBoost::VERSION}"
end

task :default => :test
