--TEST--
CommonMark\Node Parent None
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->getParent()) {
	echo "OK";
}
?>
--EXPECT--
OK
