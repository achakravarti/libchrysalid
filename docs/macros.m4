ifdef(`MAN',
	`define(__NAME__, `# NAME')',
	`define(__NAME__, `## Name')')dnl

ifdef(`MAN',
	`define(__SYNOPSIS__, `# SYNOPSIS')',
	`define(__SYNOPSIS__, `## Synopsis')')dnl

ifdef(`MAN',
	`define(__DESCRIPTION__, `# DESCRIPTION')',
	`define(__DESCRIPTION__, `## Description')')dnl

ifdef(`MAN',
	`define(__FILES__, `# FILES')',
	`define(__FILES__, `## Files')')dnl

ifdef(`MAN',
	`define(__EXAMPLES__, `# EXAMPLES')',
	`define(__EXAMPLES__, `## Examples')')dnl

ifdef(`MAN',
	`define(__CONFORMINGTO__, `# CONFORMING TO')',
	`define(__CONFORMINGTO__, `## Conforming To')')dnl

ifdef(`MAN',
	`define(__NOTES__, `# NOTES')',
	`define(__NOTES__, `## Notes')')dnl


ifdef(`MAN',
	`define(__SEEALSO__, `# SEE ALSO')',
	`define(__SEEALSO__, `## See Also')')dnl

changequote(!!, ||)

ifdef(!!MAN||,
	!!define(__COLOPHON__, 
	!!# COLOPHON

	This page is part of release 0.0.1 of the libchrysalis project.
	The latest version of this project can be found at
	[GitHub](https://github.com/achakravarti/libchrysalis).||)||,
	!!define(__COLOPHON__, !!||)||)dnl

ifdef(!!MAN||,
	!!define(__COPYRIGHT__, 
	!!# COPYRIGHT

	Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

	`libchrysalis` along with its documentation are released under the BSD
	2-Clause License. See **libchrysalis:license(7)** for the full License
	text.||)||,
	!!define(__COPYRIGHT__, !!||)||)dnl

changequote()

