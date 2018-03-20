--TEST--
CommonMark\Node endLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->endLine == 2) {
	echo "OK";
}
?>
--EXPECT--
OK
