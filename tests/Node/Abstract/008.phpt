--TEST--
CommonMark\Node Next Return
--FILE--
<?php
$document = new CommonMark\Node\Document;

$document->appendChild($p[] = new CommonMark\Node\Paragraph);
$document->appendChild($p[] = new CommonMark\Node\Paragraph);

if ($document->firstChild->next && count($p)==2) {
	echo "OK";
}
?>
--EXPECT--
OK
