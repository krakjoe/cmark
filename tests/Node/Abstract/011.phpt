--TEST--
CommonMark\Node Parent None
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->parent) {
	echo "OK";
}
?>
--EXPECT--
OK
