--TEST--
CommonMark\Node Parent
--FILE--
<?php
$document = new CommonMark\Node\Document;
$paragraph = new CommonMark\Node\Paragraph;

$document->appendChild($paragraph);

if ($paragraph->parent) {
	echo "OK";
}
?>
--EXPECT--
OK
