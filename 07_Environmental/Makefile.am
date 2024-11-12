bin_PROGRAMS = rhasher

key_SOURCES = src/rhasher.c

TESTS = tests.sh

tests.sh:
	echo "abcde" > test_file
	echo "Sha1 test_file" | ./rhash > output_rhashc
	echo " test_file" >> output_rhashc
	echo test_file | sha1sum > output_sha
	diff output_rhashc output_sha
	echo "md5 test_file" | ./rhash > output_rhashc
	echo " test_file" >> output_rhashc
	echo test_file | md5sum > output_md
	diff output_rhashc output_md
	rm -f test_file output_sha output_md output rhashc
