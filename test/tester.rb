#!/usr/bin/env ruby

if ARGV.count != 1
    puts "usage: #{$PROGRAM_NAME} path-to-emregex-executable"
    exit 1
end

$emregex = ARGV[0]

class String
    def match?(input)
        input.gsub!("\\", "\\\\\\\\")
        @output = `echo '#{input}' | #{$emregex} "#{self}"`
        return $?.success?
    end

    def should_match(*inputs)
        for input in inputs
            p input
            if not match? input
                report_error(input)
            end
        end
    end

    def should_not_match(*inputs)
        for input in inputs
            p input
            if match? input
                report_error(input)
            end
        end
    end

    def report_error(input)
        puts "TEST FAILED"
        puts "regex: #{self}"
        puts "input: #{input}"
        puts "output: #{@output}"
        exit 1
    end
end

def check(regex, &block)
    block.call(regex)
end

check "abc" do |p|
    p.should_match "abc"
    p.should_not_match "ab", "abcc"
end

check "a*" do |p|
    p.should_match "", "a", "aa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    p.should_not_match "b", "aba", "aaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaa"
end

check "ab*c" do |p|
    p.should_match "ac", "abc", "abbc", "abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbc"
    p.should_not_match "ababc", "aabc", "abcccccccccccc", "ab"
end

check "a*a" do |p|
    p.should_match "a", "aa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    p.should_not_match "", "aba"
end

check "a?" do |p|
    p.should_match "", "a"
    p.should_not_match "aa"
end

check "aa?b?" do |p|
    p.should_match "a", "aa", "ab", "aab"
end

check "(ab)*" do |p|
    p.should_match "", "ab", "abab"
    p.should_not_match "a", "aa", "abb", "aba"
end

check "(ab)?" do |p|
    p.should_match "", "ab"
    p.should_not_match "abab", "a", "aa", "abb", "aba"
end

check "abc(def)" do |p|
    p.should_match "abcdef"
    p.should_not_match "abc", "def", "abcd", "cdef", "abcf"
end

check "a.b" do |p|
    p.should_match "acb", "aab", "a b", "a.b", "a\\b"
    p.should_not_match "ab", "a\\\\b"
end

check "a\\.b" do |p|
    p.should_match "a.b"
    p.should_not_match "acb", "aab", "a b", "a\\b",  "ab",  "a\\\\b"
end

check "\\d*" do |p|
    p.should_match "0123456789", ""
    p.should_not_match " ", "d",  "\\d",  "-"
end

check "\\D\\D?" do |p|
    p.should_match "a",  "aa"
    p.should_not_match "0", "a0", "0a"
end

check "[a-c]*" do |p|
    p.should_match "", "a", "b", "c", "ab", "cc", "abc"
    p.should_not_match "d", "ad"
end

check "[abc]*" do |p|
    p.should_match "", "a", "b", "c", "ab", "cc", "abc"
    p.should_not_match "d", "ad"
end

check "[^bcd]*" do |p|
    p.should_match "a", "e", "ae"
    p.should_not_match "b", "c", "d", "ad"
end

check "[^b-d]*" do |p|
    p.should_match "a", "e", "ae"
    p.should_not_match "b", "c", "d", "ad"
end

require_relative "errors"
require_relative "ast_printer_test"
require_relative "benchmark"
