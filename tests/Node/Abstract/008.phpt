--TEST--
CommonMark\Node Next Return
--FILE--
<?php
$document = new CommonMark\Node\Document;

$document->appendChild($p[] = new CommonMark\Node\Paragraph);
$document->appendChild($p[] = new CommonMark\Node\Paragraph);

$first = $document->getFirstChild();

if ($first->getNext() && count($p)==2) {
	echo "OK";
}
?>
--EXPECT--
OK
