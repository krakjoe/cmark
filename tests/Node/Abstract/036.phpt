--TEST--
CommonMark\Node getEndColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

if ($doc->getEndColumn() == 5) {
	echo "OK";
}
?>
--EXPECT--
OK
