#!/usr/bin/env ruby

if ARGV.count != 1
    puts "usage: #{$PROGRAM_NAME} path-to-emregex-executable"
    exit 1
end

$emregex = ARGV[0]

class String
    def match?(input)
        @output = `echo "#{input}" | #{$emregex} "#{self}"`
        return $?.success?
    end

    def should_match(input)
        if not match? input
            report_error(input)
        end
    end

    def should_not_match(input)
        if match? input
            report_error(input)
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

    p.should_not_match "ab"
    p.should_not_match "abcc"
end

check "a*" do |p|
    p.should_match ""
    p.should_match "a"
    p.should_match "aa"
    p.should_match "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

    p.should_not_match "b"
    p.should_not_match "aba"
    p.should_not_match "aaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
end

check "ab*c" do |p|
    p.should_match "ac"
    p.should_match "abc"
    p.should_match "abbc"
    p.should_match "abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbc"

    p.should_not_match "ababc"
    p.should_not_match "aabc"
    p.should_not_match "abcccccccccccc"
    p.should_not_match "ab"
end

check "a*a" do |p|
    p.should_match "a"
    p.should_match "aa"
    p.should_match "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

    p.should_not_match ""
    p.should_not_match "aba"
end

check "a?" do |p|
    p.should_match ""
    p.should_match "a"

    p.should_not_match "aa"
end

check "aa?b?" do |p|
    p.should_match "a"
    p.should_match "aa"
    p.should_match "ab"
    p.should_match "aab"
end
