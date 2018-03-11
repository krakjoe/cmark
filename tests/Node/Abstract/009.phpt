--TEST--
CommonMark\Node Previous Return
--FILE--
<?php
$document = new CommonMark\Node\Document;

$document->appendChild(new CommonMark\Node\Paragraph);
$document->appendChild(new CommonMark\Node\Paragraph);

$last = $document->getLastChild();

if ($last->getPrevious()) {
	echo "OK";
}
?>
--EXPECT--
OK
