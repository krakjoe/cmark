--TEST--
CommonMark\Node getStartColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->getStartColumn() == 1) {
	echo "OK";
}
?>
--EXPECT--
OK
