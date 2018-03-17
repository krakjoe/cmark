--TEST--
CommonMark\Node getStartLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->getStartLine() == 1) {
	echo "OK";
}
?>
--EXPECT--
OK
