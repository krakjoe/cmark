--TEST--
CommonMark\Node endColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->endColumn == 5) {
	echo "OK";
}
?>
--EXPECT--
OK
