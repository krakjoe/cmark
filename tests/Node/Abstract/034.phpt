--TEST--
CommonMark\Node getEndLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->getEndLine() == 2) {
	echo "OK";
}
?>
--EXPECT--
OK
