--TEST--
CommonMark\Render Man Width
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOF
words on new lines
EOF
);
echo CommonMark\Render\Man(
	$doc, 
	CommonMark\Render\Normal, 5);
?>
--EXPECT--
.PP
words
on
new
lines


