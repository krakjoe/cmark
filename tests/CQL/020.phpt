--TEST--
CommonMark\CQL constraint Emphasis
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
emphasis *here*
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Emphasis)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Text\Emphasis) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

