--TEST--
CommonMark\Node startLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->startLine == 1) {
	echo "OK";
}
?>
--EXPECT--
OK
