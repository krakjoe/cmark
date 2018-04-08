--TEST--
CommonMark\CQL siblings
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
* item 1
* item 2
EOD
);

$call = new \CommonMark\CQL("
/firstChild(List)[
	/firstChild(Item)[
		/siblings(Item)[
			/firstChild(Paragraph)[
				/children(Text)
			]
		]
	]
]
");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Text && $node->literal == "item 2") {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

