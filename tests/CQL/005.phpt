--TEST--
CommonMark\CQL parent
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
Paragraph
EOD
);

$call = new \CommonMark\CQL("/firstChild/parent");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Document) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

