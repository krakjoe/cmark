--TEST--
CommonMark\Node Previous Return
--FILE--
<?php
$document = new CommonMark\Node\Document;

$document->appendChild(new CommonMark\Node\Paragraph);
$document->appendChild(new CommonMark\Node\Paragraph);

if ($document->lastChild->previous) {
	echo "OK";
}
?>
--EXPECT--
OK
