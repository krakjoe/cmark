--TEST--
CommonMark\Node startColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->startColumn == 1) {
	echo "OK";
}
?>
--EXPECT--
OK
